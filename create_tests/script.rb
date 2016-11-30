#!/usr/bin/env ruby


# This is bad code and I am sorry
# In order to use this script give it 2 command line arguments
# Make sure to redirect output to the file you want
# usage: ./script.rb [num_nodes] [num_colors] > output_file

max_nodes = ARGV[0].to_i
max_colors = ARGV[1].to_i
file = File.new("list_of_colors.txt", 'r').read.split

print file.sample(max_colors).join(" ")
puts ""


str = String.new
nodes = String.new
arr = (0..max_nodes-1).to_a
(0...max_nodes).each do |i|
  str += i.to_s + " "
  rand_num = rand(1..max_nodes-1)
  arr.sample(rand_num).each do |n|
    nodes += i.to_s + " " + n.to_s + "\n" 
  end

  #range = first_num..second_num
  #(range.first).downto(range.last).each do |n|
  #  if n != i
  #    nodes += i.to_s  + " " + n.to_s + "\n"
  #  end
  #end
end
puts str
puts nodes

