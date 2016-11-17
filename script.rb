#!/usr/bin/env ruby


# This is bad code and I am sorry

max_nodes = ARGV[0].to_i
max_colors = ARGV[1].to_i
file = File.new("list_of_colors.txt", 'r').read.split

print file.sample(max_colors).join(" ")
puts ""


str = String.new
nodes = String.new
(0...max_nodes).each do |i|
  str += i.to_s + " "
  first_num = rand(0..max_nodes-1)
  second_num = rand(0..max_nodes-1)
  (first_num...second_num).each do |n|
    if n == i
    else
      nodes += i.to_s  + " " + n.to_s + "\n"
    end
  end
end
puts str
puts nodes

