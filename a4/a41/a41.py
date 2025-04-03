#!/usr/bin/env python
"""Assignment 4 Part 1 Version 3"""
print(__doc__)

from typing import IO, NamedTuple
from collections import namedtuple

# Define named tuples for cleaner code
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
    def __init__(self, width: int, height: int, indent_level: int = 0) -> None:
        super().__init__(indent_level)
        self.width: int = width
        self.height: int = height
        self.shapes = []
        
    def add_shape(self, shape: HtmlComponent) -> None:
        """add_shape method"""
        shape.indent_level = self.indent_level + 1
        self.shapes.append(shape)
    
    def open_canvas(self, file: IO[str]) -> None:
        """open_canvas method"""
        self.write_comment(file, "Define SVG drawing box")
        self.write_line(file, f'<svg width="{self.width}" height="{self.height}">')
    
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

def create_demo_art() -> HtmlDocument:
    """create_demo_art method"""
    # Create the HTML document
    doc = HtmlDocument("My Art")
    
    # Create the SVG canvas
    canvas = SvgCanvas(500, 300)
    
    # Add red circles at the top
    red_color = ColorRGBA(255, 0, 0, 1.0)
    canvas.add_shape(CircleShape(Point(50, 50), 50, red_color))
    canvas.add_shape(CircleShape(Point(150, 50), 50, red_color))
    canvas.add_shape(CircleShape(Point(250, 50), 50, red_color))
    canvas.add_shape(CircleShape(Point(350, 50), 50, red_color))
    canvas.add_shape(CircleShape(Point(450, 50), 50, red_color))
    
    # Add blue circles at the bottom
    blue_color = ColorRGBA(0, 0, 255, 1.0)
    canvas.add_shape(CircleShape(Point(50, 250), 50, blue_color))
    canvas.add_shape(CircleShape(Point(150, 250), 50, blue_color))
    canvas.add_shape(CircleShape(Point(250, 250), 50, blue_color))
    canvas.add_shape(CircleShape(Point(350, 250), 50, blue_color))
    canvas.add_shape(CircleShape(Point(450, 250), 50, blue_color))
    
    # Set the canvas to the document
    doc.set_canvas(canvas)
    
    return doc

def main() -> None:
    """main method"""
    # Create and save the art
    doc = create_demo_art()
    doc.save("a41.html")

if __name__ == "__main__":
    main()