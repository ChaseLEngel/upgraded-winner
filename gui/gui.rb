#!/usr/bin/ruby
require 'gtk3'

class Node
  attr_accessor :x, :y
  def initialize(cairo, id, x, y)
    @x = x
    @y = y
    @id = id
    drawNode(cairo)
    setId(cairo)
  end

  def link(cairo, node)
    cairo.move_to @x, @y
    cairo.line_to node.x, node.y
    cairo.stroke
  end

  def setColor(cairo, color)
    cairo.move_to @x, @y
    cairo.set_source_rgb(0.3, 0.2, 0.6)
    cairo.fill
  end

  private

  def drawNode(cairo)
    radius = 20
    cairo.set_source_rgb(0.1, 0.1, 0.2)
    # Draw a circle
    cairo.arc @x, @y, radius, 0, 2*Math::PI
    # Draw outline of circle
    cairo.stroke
  end

  def setId(cairo)
    cairo.move_to @x, @y
    cairo.show_text @id
    cairo.stroke
  end

end

# Create new Gtk window instance
window = Gtk::Window.new(:toplevel)

window.set_title 'Graph Coloring'

# When window close button is clicked, exit program.
window.signal_connect('destroy') { Gtk.main_quit }

WIN_X = 500
WIN_Y = 800
window.set_default_size WIN_X, WIN_Y
window.set_window_position :center

# Create new drawing space.
draw_window = Gtk::DrawingArea.new

draw_window.queue_draw_area(0, 0, WIN_X, WIN_Y)
positions = [
  {x: 40, y: 40},
  {x: 80, y: 80},
  {x: 120, y: 80},
]

nodes = []

# Listen for Gtk to call draw event.
draw_window.signal_connect('draw') do 
  @cr = draw_window.window.create_cairo_context
  @cr.select_font_face "Purisa", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL
  @cr.set_font_size 13 

  # Draw nodes and edges
  nodes << Node.new(@cr, '0', positions[0][:x], positions[0][:y])
  nodes << Node.new(@cr, '1', positions[1][:x], positions[1][:y])
  true
end

window.add draw_window

draw_window.add_tick_callback do |_, frame_clock|
  # Update node colors
  n = Node.new(@cr, '2', rand(WIN_X), rand(WIN_Y) )
  n.setColor(@cr, :red)
end

window.show_all


Gtk.main

