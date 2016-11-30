#!/usr/bin/ruby

require 'gtk3'

require_relative 'libs/node'
require_relative 'libs/input'
require_relative 'libs/options'

options = Options.parse

WIN_X = options[:width] || 700
WIN_Y = options[:height] || 400
NODE_RADIUS = options[:radius] || 15
FONT_SIZE = options[:font_size] || 15

# Parse input file for nodes and what color nodes get set to.
nodes, coloring = Input.parse options[:file]

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
R_KEY = 114

# Create new drawing space.
@draw_window = Gtk::DrawingArea.new
# Set draw area to entire window.
@draw_window.set_size_request WIN_X, WIN_Y

# Listen for Gtk to call draw event.
@draw_window.signal_connect('draw') do
  @cr = @draw_window.window.create_cairo_context
  @cr.select_font_face "Purisa", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL
  @cr.set_line_width 1
  @cr.set_font_size FONT_SIZE

  # Tell all nodes to draw.
  nodes.each { |n| n.draw @cr }
end

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
  # Reset the graph.
  elsif event_key.keyval == R_KEY
    nodes, coloring = Input.parse options[:file]
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
