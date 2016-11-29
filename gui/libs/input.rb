require 'ostruct'
require_relative 'node'

module Input

  def self.parse(file)
    # Parse input file
    nodes = []
    coloring = []
    ntag, etag, ctag, rtag = false
    File.foreach(file) do |line|
      if line.match('#nodes')
        ntag = true
      elsif line.match('#edges')
        ntag = false
        etag = true
      elsif line.match '#coloring'
        ntag = false
        etag = false
        ctag = true
      elsif line.match('#results')
        ntag = false
        etag = false
        ctag = false
        rtag = true
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
      elsif ctag
        next if line == "#coloring\n"
        node_id = line.split[0]
        node = nodes[nodes.index { |n| n.id == node_id }]
        color = line.split[1]
        color = 'WHITE' if color.nil?
        coloring << OpenStruct.new(node: node, color: color)
      elsif rtag
        break
      end
    end
    return nodes, coloring
  end

end
