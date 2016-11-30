# Holds node information parsed from input file.
class Node
  attr_accessor :color, :id, :edges, :x, :y
  def initialize(id)
    @id = id 
    @edges = []
    @x = rand(30...WIN_X-30)
    @y = rand(30...WIN_Y-30)
    # Default color to represent uncolored node.
    @color = 'WHITE'
  end

  def draw(cr)
    # Set circle color.
    cr.set_source_rgb rgbEncode(@color)
    # Draw circle
    cr.arc @x, @y, NODE_RADIUS, 0, 2*Math::PI
    # Color circle
    cr.fill
    cr.move_to @x, @y
    cr.set_source_rgb rgbEncode('BLACK')
    # Draw node id
    cr.show_text @id
    cr.stroke
    # Draw lines to other nodes.
    @edges.each do |e|
      cr.move_to @x, @y
      cr.set_source_rgb rgbEncode('BLACK')
      cr.line_to e.x, e.y
      cr.stroke
    end
  end

  private
  def rgbEncode(color)
    gtk_color_constant = Object.const_get "Cairo::Color::#{color}"
    rgb = Cairo::Color.parse gtk_color_constant
    return rgb.red, rgb.green, rgb.blue
  end
end
