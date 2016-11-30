require 'optparse'

module Options
  def self.parse
    options = {}
    OptionParser.new do |opts|
      opts.banner = "Usage: gui.rb -f [file] [options]"

      opts.on("-f=", "--file=", "Output from wumpus") do |f|
        options[:file] = f
      end

      opts.on("-w=", "--width=", "Size of window width") do |w|
        options[:width] = w.to_i
      end

      opts.on("-h=", "--height=", "Size of window height") do |h|
        options[:height] = h.to_i
      end

      opts.on("-r=", "--radius=", "Radius of nodes") do |r|
        options[:radius] = r.to_i
      end

      opts.on("-s=", "--size=", "Size of font") do |s|
        options[:font_size] = s.to_i
      end
    end.parse!
    options
  end
end
