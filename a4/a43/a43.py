#!/usr/bin/env python3
"""Assignment 4 Part 3 - SENG 265 Python Arts Program"""

from collections import namedtuple
from typing import List, Optional, Tuple, NamedTuple
import random

# Named tuples for representing colors, positions, and dimensions
Color = namedtuple('Color', ['r', 'g', 'b', 'opacity'])
Position = namedtuple('Position', ['x', 'y'])
Dimension = namedtuple('Dimension', ['width', 'height'])

class HtmlComponent:
    """HtmlComponent class"""
    
    def __init__(self, tag: str, attributes: Optional[dict] = None, content: Optional[str] = None):
        """__init__() method"""
        self.tag = tag
        self.attributes = attributes or {}
        self.content = content
        self.children: List[HtmlComponent] = []
    
    def add_child(self, child: 'HtmlComponent') -> None:
        """add_child() method"""
        self.children.append(child)
    
    def render(self, indent: int = 0) -> str:
        """render() method"""
        indent_str = " " * indent
        result = f"{indent_str}<{self.tag}"
        
        for key, value in self.attributes.items():
            result += f' {key}="{value}"'
        
        if not self.content and not self.children:
            result += " />\n"
            return result
        
        result += ">\n"
        
        if self.content:
            result += f"{indent_str}  {self.content}\n"
        
        for child in self.children:
            result += child.render(indent + 2)
        
        result += f"{indent_str}</{self.tag}>\n"
        return result


class HtmlDocument:
    """HtmlDocument class"""
    
    def __init__(self, title: str):
        """__init__() method"""
        self.title = title
        self.head = HtmlComponent("head")
        self.body = HtmlComponent("body")
        self.head.add_child(HtmlComponent("title", content=title))
        
    def add_to_body(self, component: HtmlComponent) -> None:
        """add_to_body() method"""
        self.body.add_child(component)
        
    def render(self) -> str:
        """render() method"""
        result = "<!DOCTYPE html>\n"
        html = HtmlComponent("html")
        html.add_child(self.head)
        html.add_child(self.body)
        result += html.render()
        return result
    
    def save_to_file(self, filename: str) -> None:
        """save_to_file() method"""
        with open(filename, 'w') as file:
            file.write(self.render())


class SvgCanvas(HtmlComponent):
    """SvgCanvas class"""
    
    def __init__(self, width: int, height: int, background_color: str = "white"):
        """__init__() method"""
        attributes = {
            "width": width,
            "height": height,
            "xmlns": "http://www.w3.org/2000/svg"
        }
        super().__init__("svg", attributes)
        self.background = RectangleShape(
            position=Position(0, 0),
            dimension=Dimension(width, height),
            fill=background_color
        )
        self.add_child(self.background)
    
    def add_shape(self, shape: 'Shape') -> None:
        """add_shape() method"""
        self.add_child(shape)
    
    def gen_art(self, shapes: List['Shape']) -> None:
        """gen_art() method"""
        for shape in shapes:
            self.add_shape(shape)


class Shape(HtmlComponent):
    """Shape class"""
    
    def __init__(self, tag: str, attributes: dict):
        """__init__() method"""
        super().__init__(tag, attributes)


class CircleShape(Shape):
    """CircleShape class"""
    
    def __init__(self, position: Position, radius: int, fill: str, opacity: float = 1.0):
        """__init__() method"""
        attributes = {
            "cx": position.x,
            "cy": position.y,
            "r": radius,
            "fill": fill,
            "opacity": opacity
        }
        super().__init__("circle", attributes)


class RectangleShape(Shape):
    """RectangleShape class"""
    
    def __init__(self, position: Position, dimension: Dimension, fill: str, opacity: float = 1.0):
        """__init__() method"""
        attributes = {
            "x": position.x,
            "y": position.y,
            "width": dimension.width,
            "height": dimension.height,
            "fill": fill,
            "opacity": opacity
        }
        super().__init__("rect", attributes)


class EllipseShape(Shape):
    """EllipseShape class"""
    
    def __init__(self, position: Position, rx: int, ry: int, fill: str, opacity: float = 1.0):
        """__init__() method"""
        attributes = {
            "cx": position.x,
            "cy": position.y,
            "rx": rx,
            "ry": ry,
            "fill": fill,
            "opacity": opacity
        }
        super().__init__("ellipse", attributes)


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
                 shape_types: List[str] = None):
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
    
    def __init__(self, config: PyArtConfig):
        """__init__() method"""
        self.config = config
        self.shape_type = random.choice(config.shape_types)
        self.position = Position(
            random.randint(0, config.canvas_width),
            random.randint(0, config.canvas_height)
        )
        self.radius = random.randint(config.radius_min, config.radius_max)
        self.width = random.randint(config.width_min, config.width_max)
        self.height = random.randint(config.height_min, config.height_max)
        self.color = Color(
            random.randint(config.red_min, config.red_max),
            random.randint(config.green_min, config.green_max),
            random.randint(config.blue_min, config.blue_max),
            random.uniform(config.opacity_min, config.opacity_max)
        )
    
    def __str__(self) -> str:
        """__str__() method"""
        result = f"Shape Type: {self.shape_type}\n"
        result += f"Position: ({self.position.x}, {self.position.y})\n"
        
        if self.shape_type == "circle":
            result += f"Radius: {self.radius}\n"
        else:
            result += f"Width: {self.width}\n"
            result += f"Height: {self.height}\n"
        
        result += f"Color: rgb({self.color.r}, {self.color.g}, {self.color.b})\n"
        result += f"Opacity: {self.color.opacity:.2f}"
        return result
    
    def as_Part2_line(self) -> str:
        """as_Part2_line() method"""
        shape_id = {"circle": 1, "rectangle": 2, "ellipse": 3}.get(self.shape_type, 0)
        return f"{shape_id:3d} {self.position.x:4d} {self.position.y:4d} {self.radius:3d} {self.width:4d} {self.height:4d} {self.color.r:3d} {self.color.g:3d} {self.color.b:3d} {self.color.opacity:.2f}"
    
    def as_svg(self) -> Shape:
        """as_svg() method"""
        fill = f"rgb({self.color.r}, {self.color.g}, {self.color.b})"
        
        if self.shape_type == "circle":
            return CircleShape(self.position, self.radius, fill, self.color.opacity)
        elif self.shape_type == "rectangle":
            return RectangleShape(self.position, Dimension(self.width, self.height), fill, self.color.opacity)
        elif self.shape_type == "ellipse":
            return EllipseShape(self.position, self.width // 2, self.height // 2, fill, self.color.opacity)
        else:
            # Default to circle if shape type is unknown
            return CircleShape(self.position, self.radius, fill, self.color.opacity)


def generate_art(config: PyArtConfig, title: str, filename: str) -> None:
    """Generate art based on configuration and save to file"""
    # Create HTML document
    doc = HtmlDocument(title)
    
    # Create SVG canvas
    canvas = SvgCanvas(config.canvas_width, config.canvas_height, config.background_color)
    
    # Generate random shapes
    shapes = []
    for _ in range(config.num_shapes):
        random_shape = RandomShape(config)
        shapes.append(random_shape.as_svg())
    
    # Add shapes to canvas
    canvas.gen_art(shapes)
    
    # Add canvas to document
    doc.add_to_body(canvas)
    
    # Save to file
    doc.save_to_file(filename)


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
        background_color="white"
    )
    
    # Generate art with each configuration
    generate_art(config1, "Colorful Circles", "a431.html")
    generate_art(config2, "Rectangles and Ellipses", "a432.html")
    generate_art(config3, "Mixed Shapes - Blue Theme", "a433.html")
    
    print("Art generation complete. Files saved as a431.html, a432.html, and a433.html")


if __name__ == "__main__":
    main()