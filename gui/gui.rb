#!/usr/bin/ruby
require 'gtk3'

WIN_X = 1000
WIN_Y = 1000

# Holds node information parsed from input file.
class Node
  attr_accessor :color, :id, :edges, :x, :y
  def initialize(id, x, y)
    @id = id 
    @edges = []
    @x = x
    @y = y
  end

  def addEdge(node)
    @edges << node
  end
end

# Parse input file
nodes = []
ntag, etag, rtag = false
File.foreach(ARGV.first) do |line|
  if line.match('#nodes')
    ntag = true
  elsif line.match('#edges')
    ntag = false
    etag = true
  elsif line.match('#results')
    ntag = false
    etag = false
    rtag = true
  elsif line.match('Rejected')
    puts 'Rejected'
    exit
  end

  if ntag
    next if line == "#nodes\n"
    # Create node with random x/y position.
    nodes << Node.new(line.chomp, rand(WIN_X-30), rand(WIN_Y-30))
  elsif etag
    next if line == "#edges\n"
    from = line.split[0]
    to = line.split[1]
    from_node = nodes[nodes.index { |n| n.id == from }]
    to_node = nodes[nodes.index { |n| n.id == to }]
    from_node.addEdge(to_node)
  elsif rtag
    next if line == "#results\n"
    id = line.split[0]
    color = line.split[1]
    node = nodes[nodes.index { |n| n.id == id }]
    node.color = color
  end
end

# Create new Gtk window instance
window = Gtk::Window.new(:toplevel)
window.set_default_size WIN_X, WIN_Y

ENTER_KEY = 65293
SPACE_KEY = 32

window.set_title 'Graph Coloring'

# When window close button is clicked, exit program.
window.signal_connect('destroy') { Gtk.main_quit }

window.set_window_position :center

# Create new drawing space.
@draw_window = Gtk::DrawingArea.new
@draw_window.set_size_request WIN_X, WIN_Y

def encodeColor(color)
  rgb = Cairo::Color.parse(Object.const_get("Cairo::Color::#{color}"))
  return rgb.red, rgb.green, rgb.blue
end

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
@draw_window.signal_connect('draw') do 
  draw(nodes)
end

window.signal_connect('key-press-event') do |_widget, event_key|
  if event_key.keyval == SPACE_KEY
    nodes.each do |n|
      n.x = rand(WIN_X-30)
      n.y = rand(WIN_Y-30)
    end
  elsif event_key.keyval == ENTER_KEY
    # Next iteration
  end
  # Tell GTK that @draw_window needs to be redrawn.
  @draw_window.queue_draw
end

window.add @draw_window

# Show all widgets on window.
window.show_all

Gtk.main
