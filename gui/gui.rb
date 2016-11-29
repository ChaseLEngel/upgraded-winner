#!/usr/bin/ruby
require 'gtk3'
require_relative 'libs/node'
require_relative 'libs/input'

WIN_X = 1000
WIN_Y = 1000

# Parse input file for nodes and what color nodes get set to.
nodes, coloring = Input.parse(ARGV.first)

# Create new Gtk window instance
window = Gtk::Window.new(:toplevel)
window.set_default_size WIN_X, WIN_Y
window.set_title 'Graph Coloring'
# When window close button is clicked, exit program.
window.signal_connect('destroy') { Gtk.main_quit }
window.set_window_position :center

# Define key maps.
ENTER_KEY = 65293
SPACE_KEY = 32

# Create new drawing space.
@draw_window = Gtk::DrawingArea.new
# Set draw area to entire window.
@draw_window.set_size_request WIN_X, WIN_Y

# Takes string color and converts it to red, green, blue values.
def encodeColor(color)
  rgb = Cairo::Color.parse(Object.const_get("Cairo::Color::#{color}"))
  return rgb.red, rgb.green, rgb.blue
end

# Draws everything.
def draw(nodes)
  @cr = @draw_window.window.create_cairo_context
  @cr.select_font_face "Purisa", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL
  @cr.set_font_size 15

  # Draw nodes and edges
  nodes.each do |n|
    # Set circle color.
    @cr.set_source_rgb(encodeColor(n.color))
    # Draw circle
    @cr.arc n.x, n.y, 20, 0, 2*Math::PI
    # Color circle
    @cr.fill
    @cr.move_to n.x, n.y
    @cr.set_source_rgb(encodeColor('BLACK'))
    # Draw node id
    @cr.show_text n.id
    @cr.stroke
    # Draw lines to other nodes.
    n.edges.each do |e|
      @cr.move_to n.x, n.y
      @cr.set_source_rgb(encodeColor('BLACK'))
      @cr.line_to e.x, e.y
      @cr.stroke
    end
  end
end

# Listen for Gtk to call draw event.
@draw_window.signal_connect('draw') { draw nodes }

# Updates nodes and calls draw event.
window.signal_connect('key-press-event') do |_widget, event_key|
  # Randomize all node positions.
  if event_key.keyval == SPACE_KEY
    nodes.each do |n|
      n.x = rand(WIN_X-30)
      n.y = rand(WIN_Y-30)
    end
  # Color next node.
  elsif event_key.keyval == ENTER_KEY && !coloring.empty?
    # Get first on stack
    struct = coloring.take(1)[0]
    # Update node color.
    struct.node.color = struct.color
    # Resize stack
    coloring = coloring.drop(1)
  end
  # Tell GTK that @draw_window needs to be redrawn.
  @draw_window.queue_draw
end

# Tell Gtk window about drawing.
window.add @draw_window

# Show all widgets on window.
window.show_all

# Gtk blocking call to wait for events.
Gtk.main
