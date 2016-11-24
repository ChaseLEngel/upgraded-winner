#!/usr/bin/ruby
require 'gtk3'

class Node
  def initialize(cairo, id, x, y)
    @cairo = cairo
    drawNode(x, y)
    #@cairo.move_to x, y
    #@cairo.show_text id
  end

  private
  def drawNode(x, y)
    # Draw a circle
    arc = @cairo.arc x, y, 20, 0, 2*Math::PI
    # Draw outline of circle
    arc.stroke
  end
end

# Create new Gtk window instance
window = Gtk::Window.new(:toplevel)

window.set_title 'Graph Coloring'

# When window close button is clicked, exit program.
window.signal_connect('destroy') { Gtk.main_quit }

WIN_X = 200
WIN_Y = 200
window.set_default_size WIN_X, WIN_Y
window.set_window_position :center

# Create new drawing space.
draw_window = Gtk::DrawingArea.new

# Listen for Gtk to call draw event.
draw_window.signal_connect('draw') do 
  @cr = draw_window.window.create_cairo_context
  @cr.select_font_face "Purisa", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL
  @cr.set_font_size 13 

  # Draw nodes and edges
end

draw_window.add_tick_callback do |_, frame_clock|
  # Update node colors
  Node.new(@cr, '0', rand(20..WIN_X-20), rand(20..WIN_Y-20))
  draw_window.queue_draw
end

window.add draw_window
window.show_all

Gtk.main
