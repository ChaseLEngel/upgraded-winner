#!/usr/bin/ruby
require 'gtk3'

WIN_X = 700
WIN_Y = 400

positions = [
  {x: 30, y: 30},
  {x: WIN_X-30, y: 30},
  {x: 30, y: 80},
  {x: 120, y: 100},
  {x: 160, y: 100},
  {x: 200, y: 160},
]

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

window.set_title 'Graph Coloring'

# When window close button is clicked, exit program.
window.signal_connect('destroy') { Gtk.main_quit }

window.set_default_size WIN_X, WIN_Y
window.set_window_position :center

# Create new drawing space.
draw_window = Gtk::DrawingArea.new

# Listen for Gtk to call draw event.
draw_window.signal_connect('draw') do 
  @cr = draw_window.window.create_cairo_context
  @cr.select_font_face "Purisa", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL
  @cr.set_font_size 15

  # Draw nodes and edges
  nodes.each do |n|
    # Set circle color.
    color = Cairo::Color.parse(Object.const_get("Cairo::Color::#{n.color}"))
    @cr.set_source_rgb(color.red, color.green, color.blue)
    # Draw circle
    @cr.arc n.x, n.y, 20, 0, 2*Math::PI
    # Color circle
    @cr.fill
    @cr.move_to n.x, n.y
    color = Cairo::Color.parse(Cairo::Color::BLACK)
    @cr.set_source_rgb(color.red, color.green, color.blue)
    # Draw node id
    @cr.show_text n.id
    @cr.stroke
    # Draw lines to other nodes.
    n.edges.each do |e|
      @cr.move_to n.x, n.y
      color = Cairo::Color.parse(Cairo::Color::BLACK)
      @cr.set_source_rgb(color.red, color.green, color.blue)
      @cr.line_to e.x, e.y
      @cr.stroke
    end
  end
end

window.add draw_window

window.show_all

Gtk.main
