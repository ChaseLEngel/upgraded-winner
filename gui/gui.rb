#!/usr/bin/ruby
require 'gtk3'

# Create new Gtk window instance
window = Gtk::Window.new

window.set_title 'Graph Coloring'

# When window close button is clicked, exit program.
window.signal_connect('destroy') { Gtk.main_quit }

window.set_default_size 1000, 1000

# Create new drawing space.
draw_window = Gtk::DrawingArea.new

# Listen for Gtk to call draw event.
draw_window.signal_connect('draw') do 
  cr = draw_window.window.create_cairo_context

  # Set color
  cr.set_source_rgb 0.9, 0.5, 0.3

  # Draw a circle
  cr.arc 10, 160, 40, 0, 2*Math::PI
  # Fill circle with color
  cr.fill
end

window.add draw_window
window.show_all

Gtk.main
