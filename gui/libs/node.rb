# Holds node information parsed from input file.
class Node
  attr_accessor :color, :id, :edges, :x, :y
  def initialize(id, x, y)
    @id = id 
    @edges = []
    @x = x
    @y = y
    # Default color to represent uncolored node.
    @color = 'WHITE'
  end

  def addEdge(node)
    @edges << node
  end
end
