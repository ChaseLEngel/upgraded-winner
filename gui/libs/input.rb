require 'ostruct'
require_relative 'node'

module Input

  def self.parse(file)
    # If parse is called more than once only reset node color.
    unless @nodes.nil? && @coloring.nil?
      @nodes.each do |node|
        node.color = 'WHITE'
      end
      return @nodes, @coloring
    end
    # Parse input file
    @nodes = []
    @coloring = []
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
        @nodes << Node.new(line.chomp)
      elsif etag
        next if line == "#edges\n"
        from = line.split[0]
        to = line.split[1]
        from_node = @nodes[@nodes.index { |n| n.id == from }]
        to_node = @nodes[@nodes.index { |n| n.id == to }]
        from_node.edges << to_node
      elsif ctag
        next if line == "#coloring\n"
        node_id = line.split[0]
        node = @nodes[@nodes.index { |n| n.id == node_id }]
        color = line.split[1]
        color = 'WHITE' if color.nil?
        @coloring << OpenStruct.new(node: node, color: color)
      elsif rtag
        break
      end
    end
    return @nodes, @coloring
  end

end
