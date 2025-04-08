#!/usr/bin/env python3
"""Assignment 4 Part 3 - SENG 265 Python Arts Program"""

from typing import IO, List, Optional
from collections import namedtuple
import random

# Named tuples for cleaner code (from Part 1)
Point = namedtuple('Point', ['x', 'y'])
ColorRGBA = namedtuple('ColorRGBA', ['red', 'green', 'blue', 'opacity'])

class HtmlComponent:
    """HtmlComponent class"""
    def __init__(self, indent_level: int = 0) -> None:
        self.indent_level: int = indent_level
        
    def get_indent(self) -> str:
        """get_indent method"""
        return "   " * self.indent_level
    
    def write_line(self, file: IO[str], line: str) -> None:
        """write_line method"""
        file.write(f"{self.get_indent()}{line}\n")
        
    def write_comment(self, file: IO[str], comment: str) -> None:
        """write_comment method"""
        self.write_line(file, f"<!--{comment}-->")

class CircleShape(HtmlComponent):
    """CircleShape class"""
    def __init__(self, center: Point, radius: int, color: ColorRGBA, indent_level: int = 0) -> None:
        super().__init__(indent_level)
        self.center: Point = center
        self.radius: int = radius
        self.color: ColorRGBA = color
    
    def draw(self, file: IO[str]) -> None:
        """draw method"""
        line1: str = f'<circle cx="{self.center.x}" cy="{self.center.y}" r="{self.radius}" '
        line2: str = f'fill="rgb({self.color.red}, {self.color.green}, {self.color.blue})" fill-opacity="{self.color.opacity}"></circle>'
        self.write_line(file, line1 + line2)

class RectangleShape(HtmlComponent):
    """RectangleShape class"""
    def __init__(self, top_left: Point, width: int, height: int, color: ColorRGBA, indent_level: int = 0) -> None:
        super().__init__(indent_level)
        self.top_left: Point = top_left
        self.width: int = width
        self.height: int = height
        self.color: ColorRGBA = color
    
    def draw(self, file: IO[str]) -> None:
        """draw method"""
        line1: str = f'<rect x="{self.top_left.x}" y="{self.top_left.y}" width="{self.width}" height="{self.height}" '
        line2: str = f'fill="rgb({self.color.red}, {self.color.green}, {self.color.blue})" fill-opacity="{self.color.opacity}"></rect>'
        self.write_line(file, line1 + line2)

class EllipseShape(HtmlComponent):
    """EllipseShape class"""
    def __init__(self, center: Point, rx: int, ry: int, color: ColorRGBA, indent_level: int = 0) -> None:
        super().__init__(indent_level)
        self.center: Point = center
        self.rx: int = rx
        self.ry: int = ry
        self.color: ColorRGBA = color
    
    def draw(self, file: IO[str]) -> None:
        """draw method"""
        line1: str = f'<ellipse cx="{self.center.x}" cy="{self.center.y}" rx="{self.rx}" ry="{self.ry}" '
        line2: str = f'fill="rgb({self.color.red}, {self.color.green}, {self.color.blue})" fill-opacity="{self.color.opacity}"></ellipse>'
        self.write_line(file, line1 + line2)

class SvgCanvas(HtmlComponent):
    """SvgCanvas class"""
    def __init__(self, width: int, height: int, background_color: str = "white", indent_level: int = 0) -> None:
        super().__init__(indent_level)
        self.width: int = width
        self.height: int = height
        self.background_color: str = background_color
        self.shapes = []
        
    def add_shape(self, shape: HtmlComponent) -> None:
        """add_shape method"""
        shape.indent_level = self.indent_level + 1
        self.shapes.append(shape)
    
    def open_canvas(self, file: IO[str]) -> None:
        """open_canvas method"""
        self.write_comment(file, "Define SVG drawing box")
        self.write_line(file, f'<svg width="{self.width}" height="{self.height}" xmlns="http://www.w3.org/2000/svg">')
        # Add background if not white
        if self.background_color != "white":
            bg = RectangleShape(Point(0, 0), self.width, self.height, ColorRGBA(0, 0, 0, 1.0), self.indent_level + 1)
            bg.color = ColorRGBA(0, 0, 0, 1.0)  # Placeholder - will use fill attribute instead
            line = f'<rect x="0" y="0" width="{self.width}" height="{self.height}" fill="{self.background_color}"></rect>'
            self.write_line(file, "   " + line)
    
    def close_canvas(self, file: IO[str]) -> None:
        """close_canvas method"""
        self.write_line(file, "</svg>")
    
    def gen_art(self, file: IO[str]) -> None:
        """gen_art method"""
        for shape in self.shapes:
            shape.draw(file)
            
    def draw(self, file: IO[str]) -> None:
        """draw method"""
        self.open_canvas(file)
        self.gen_art(file)
        self.close_canvas(file)

class HtmlDocument(HtmlComponent):
    """HtmlDocument class"""
    def __init__(self, title: str, indent_level: int = 0) -> None:
        super().__init__(indent_level)
        self.title: str = title
        self.canvas: SvgCanvas = None
        
    def set_canvas(self, canvas: SvgCanvas) -> None:
        """set_canvas method"""
        canvas.indent_level = self.indent_level + 1
        self.canvas = canvas
    
    def write_header(self, file: IO[str]) -> None:
        """write_header method"""
        self.write_line(file, "<!DOCTYPE html>")
        self.write_line(file, "<html>")
        self.write_line(file, "<head>")
        self.indent_level += 1
        self.write_line(file, f"<title>{self.title}</title>")
        self.indent_level -= 1
        self.write_line(file, "</head>")
        self.write_line(file, "<body>")
    
    def write_footer(self, file: IO[str]) -> None:
        """write_footer method"""
        self.write_line(file, "</body>")
        self.write_line(file, "</html>")
    
    def save(self, filename: str) -> None:
        """save method"""
        with open(filename, "w") as f:
            self.write_header(f)
            if self.canvas:
                self.canvas.draw(f)
            self.write_footer(f)

class PyArtConfig:
    """PyArtConfig class"""
    # Class variables for default ranges
    DEFAULT_WIDTH = 800
    DEFAULT_HEIGHT = 600
    DEFAULT_NUM_SHAPES = 100
    DEFAULT_RADIUS_MIN = 5
    DEFAULT_RADIUS_MAX = 50
    DEFAULT_WIDTH_MIN = 10
    DEFAULT_WIDTH_MAX = 100
    DEFAULT_HEIGHT_MIN = 10
    DEFAULT_HEIGHT_MAX = 100
    DEFAULT_OPACITY_MIN = 0.1
    DEFAULT_OPACITY_MAX = 1.0
    DEFAULT_RED_MIN = 0
    DEFAULT_RED_MAX = 255
    DEFAULT_GREEN_MIN = 0
    DEFAULT_GREEN_MAX = 255
    DEFAULT_BLUE_MIN = 0
    DEFAULT_BLUE_MAX = 255
    
    def __init__(self, 
                 canvas_width: int = DEFAULT_WIDTH,
                 canvas_height: int = DEFAULT_HEIGHT,
                 num_shapes: int = DEFAULT_NUM_SHAPES,
                 radius_min: int = DEFAULT_RADIUS_MIN,
                 radius_max: int = DEFAULT_RADIUS_MAX,
                 width_min: int = DEFAULT_WIDTH_MIN,
                 width_max: int = DEFAULT_WIDTH_MAX,
                 height_min: int = DEFAULT_HEIGHT_MIN,
                 height_max: int = DEFAULT_HEIGHT_MAX,
                 opacity_min: float = DEFAULT_OPACITY_MIN,
                 opacity_max: float = DEFAULT_OPACITY_MAX,
                 red_min: int = DEFAULT_RED_MIN,
                 red_max: int = DEFAULT_RED_MAX,
                 green_min: int = DEFAULT_GREEN_MIN,
                 green_max: int = DEFAULT_GREEN_MAX,
                 blue_min: int = DEFAULT_BLUE_MIN,
                 blue_max: int = DEFAULT_BLUE_MAX,
                 background_color: str = "white",
                 shape_types: List[str] = None) -> None:
        """__init__() method"""
        self.canvas_width = canvas_width
        self.canvas_height = canvas_height
        self.num_shapes = num_shapes
        self.radius_min = radius_min
        self.radius_max = radius_max
        self.width_min = width_min
        self.width_max = width_max
        self.height_min = height_min
        self.height_max = height_max
        self.opacity_min = opacity_min
        self.opacity_max = opacity_max
        self.red_min = red_min
        self.red_max = red_max
        self.green_min = green_min
        self.green_max = green_max
        self.blue_min = blue_min
        self.blue_max = blue_max
        self.background_color = background_color
        self.shape_types = shape_types if shape_types else ["circle", "rectangle", "ellipse"]

class RandomShape:
    """RandomShape class"""
    
    def __init__(self, count: int, config: PyArtConfig) -> None:
        """__init__() method"""
        self.count = count
        self.config = config
        self.shape_type = random.choice(config.shape_types)
        
        # Generate random values based on configuration
        self.x = random.randint(0, config.canvas_width)
        self.y = random.randint(0, config.canvas_height)
        self.radius = random.randint(config.radius_min, config.radius_max)
        self.width = random.randint(config.width_min, config.width_max)
        self.height = random.randint(config.height_min, config.height_max)
        self.r = random.randint(config.red_min, config.red_max)
        self.g = random.randint(config.green_min, config.green_max)
        self.b = random.randint(config.blue_min, config.blue_max)
        self.opacity = round(random.uniform(config.opacity_min, config.opacity_max), 2)
    
    def __str__(self) -> str:
        """__str__() method"""
        shape_info = ""
        if self.shape_type == "circle":
            shape_info = f"radius={self.radius}"
        elif self.shape_type == "ellipse":
            shape_info = f"rx={self.width//2}, ry={self.height//2}"
        elif self.shape_type == "rectangle":
            shape_info = f"width={self.width}, height={self.height}"
            
        return (
            f"Shape #{self.count}:\n"
            f"  Type: {self.shape_type}\n"
            f"  Position: ({self.x}, {self.y})\n"
            f"  Size: {shape_info}\n"
            f"  Color: rgb({self.r}, {self.g}, {self.b})\n"
            f"  Opacity: {self.opacity}"
        )
    
    def as_Part2_line(self) -> str:
        """as_Part2_line() method"""
        shape_code = {"circle": "1", "rectangle": "2", "ellipse": "3"}.get(self.shape_type, "0")
        return f"{self.count:3d} {shape_code:3s} {self.x:3d} {self.y:3d} {self.radius:3d} {self.width//2:3d} {self.height//2:3d} {self.width:3d} {self.height:3d} {self.r:3d} {self.g:3d} {self.b:3d} {self.opacity:.2f}"
    
    def as_svg_shape(self) -> HtmlComponent:
        """as_svg_shape() method"""
        color = ColorRGBA(self.r, self.g, self.b, self.opacity)
        
        if self.shape_type == "circle":
            return CircleShape(Point(self.x, self.y), self.radius, color)
        elif self.shape_type == "rectangle":
            return RectangleShape(Point(self.x, self.y), self.width, self.height, color)
        elif self.shape_type == "ellipse":
            return EllipseShape(Point(self.x, self.y), self.width // 2, self.height // 2, color)
        else:
            # Default to circle if shape type is unknown
            return CircleShape(Point(self.x, self.y), self.radius, color)

def generate_art(config: PyArtConfig, title: str, filename: str) -> None:
    """Generate art based on configuration and save to file"""
    # Create HTML document
    doc = HtmlDocument(title)
    
    # Create SVG canvas
    canvas = SvgCanvas(config.canvas_width, config.canvas_height, config.background_color)
    
    # Generate random shapes
    for i in range(1, config.num_shapes + 1):
        random_shape = RandomShape(i, config)
        canvas.add_shape(random_shape.as_svg_shape())
    
    # Set canvas to document
    doc.set_canvas(canvas)
    
    # Save to file
    doc.save(filename)

def main() -> None:
    """main() function"""
    # Configuration 1: Colorful Circles
    config1 = PyArtConfig(
        canvas_width=800,
        canvas_height=600,
        num_shapes=150,
        radius_min=10,
        radius_max=30,
        opacity_min=0.3,
        opacity_max=0.7,
        shape_types=["circle"],
        background_color="black"
    )
    
    # Configuration 2: Rectangles and Ellipses
    config2 = PyArtConfig(
        canvas_width=800,
        canvas_height=600,
        num_shapes=100,
        width_min=20,
        width_max=120,
        height_min=20,
        height_max=120,
        opacity_min=0.2,
        opacity_max=0.6,
        red_min=100,
        red_max=255,
        green_min=0,
        green_max=150,
        blue_min=0,
        blue_max=150,
        shape_types=["rectangle", "ellipse"],
        background_color="#f0f0f0"
    )
    
    # Configuration 3: Mixed Shapes with Blue Theme
    config3 = PyArtConfig(
        canvas_width=800,
        canvas_height=600,
        num_shapes=200,
        radius_min=5,
        radius_max=40,
        width_min=10,
        width_max=80,
        height_min=10,
        height_max=80,
        opacity_min=0.1,
        opacity_max=0.9,
        red_min=0,
        red_max=100,
        green_min=0,
        green_max=150,
        blue_min=100,
        blue_max=255,
        shape_types=["circle", "rectangle", "ellipse"],
        background_color="black"
    )
    
    # Generate art with each configuration
    generate_art(config1, "Colorful Circles", "a431.html")
    generate_art(config2, "Rectangles and Ellipses", "a432.html")
    generate_art(config3, "Mixed Shapes - Blue Theme", "a433.html")
    
    print("Art generation complete. Files saved as a431.html, a432.html, and a433.html")

if __name__ == "__main__":
    main()