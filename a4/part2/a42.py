from collections import namedtuple
from typing import NamedTuple, List, Optional
import random

class PyArtConfig:
    """PyArtConfig class"""
    # Define default ranges as class variables
    MIN_X = 0
    MAX_X = 600
    MIN_Y = 0
    MAX_Y = 400
    MIN_RADIUS = 0
    MAX_RADIUS = 100
    MIN_ELLIPSE_RADIUS = 10
    MAX_ELLIPSE_RADIUS = 30
    MIN_RECT_DIM = 10
    MAX_RECT_DIM = 100
    MIN_COLOR = 0
    MAX_COLOR = 255
    MIN_OPACITY = 0.0
    MAX_OPACITY = 1.0
    
    def __init__(self, 
                 min_x: int = MIN_X,
                 max_x: int = MAX_X,
                 min_y: int = MIN_Y,
                 max_y: int = MAX_Y,
                 min_radius: int = MIN_RADIUS,
                 max_radius: int = MAX_RADIUS,
                 min_ellipse_radius: int = MIN_ELLIPSE_RADIUS,
                 max_ellipse_radius: int = MAX_ELLIPSE_RADIUS,
                 min_rect_dim: int = MIN_RECT_DIM,
                 max_rect_dim: int = MAX_RECT_DIM,
                 min_color: int = MIN_COLOR,
                 max_color: int = MAX_COLOR,
                 min_opacity: float = MIN_OPACITY,
                 max_opacity: float = MAX_OPACITY) -> None:
        """__init__() method"""
        self.min_x = min_x
        self.max_x = max_x
        self.min_y = min_y
        self.max_y = max_y
        self.min_radius = min_radius
        self.max_radius = max_radius
        self.min_ellipse_radius = min_ellipse_radius
        self.max_ellipse_radius = max_ellipse_radius
        self.min_rect_dim = min_rect_dim
        self.max_rect_dim = max_rect_dim
        self.min_color = min_color
        self.max_color = max_color
        self.min_opacity = min_opacity
        self.max_opacity = max_opacity

# Define a ShapeData NamedTuple to store random shape data
class ShapeData(NamedTuple):
    """ShapeData class"""
    count: int
    shape_type: str
    x: int
    y: int
    radius: int
    rx: int
    ry: int
    width: int
    height: int
    r: int
    g: int
    b: int
    opacity: float

class RandomShape:
    """RandomShape class"""
    # Define shape types
    CIRCLE = '0'
    RECTANGLE = '1'
    ELLIPSE = '3'
    
    def __init__(self, count: int, config: PyArtConfig) -> None:
        """__init__() method"""
        self.count = count
        self.config = config
        self.shape_type = random.choice([RandomShape.CIRCLE, RandomShape.RECTANGLE, RandomShape.ELLIPSE])
        
        # Generate random values based on configuration
        self.x = random.randint(self.config.min_x, self.config.max_x)
        self.y = random.randint(self.config.min_y, self.config.max_y)
        self.radius = random.randint(self.config.min_radius, self.config.max_radius)
        self.rx = random.randint(self.config.min_ellipse_radius, self.config.max_ellipse_radius)
        self.ry = random.randint(self.config.min_ellipse_radius, self.config.max_ellipse_radius)
        self.width = random.randint(self.config.min_rect_dim, self.config.max_rect_dim)
        self.height = random.randint(self.config.min_rect_dim, self.config.max_rect_dim)
        self.r = random.randint(self.config.min_color, self.config.max_color)
        self.g = random.randint(self.config.min_color, self.config.max_color)
        self.b = random.randint(self.config.min_color, self.config.max_color)
        self.opacity = round(random.uniform(self.config.min_opacity, self.config.max_opacity), 2)
        
        # Create a ShapeData object to store all values
        self.data = ShapeData(
            count=self.count,
            shape_type=self.shape_type,
            x=self.x,
            y=self.y,
            radius=self.radius,
            rx=self.rx,
            ry=self.ry,
            width=self.width,
            height=self.height,
            r=self.r,
            g=self.g,
            b=self.b,
            opacity=self.opacity
        )
    
    def __str__(self) -> str:
        """__str__() method"""
        shape_info = ""
        if self.data.shape_type == RandomShape.CIRCLE:
            shape_info = f"radius={self.data.radius}"
        elif self.data.shape_type == RandomShape.ELLIPSE:
            shape_info = f"rx={self.data.rx}, ry={self.data.ry}"
        elif self.data.shape_type == RandomShape.RECTANGLE:
            shape_info = f"width={self.data.width}, height={self.data.height}"
            
        return (
            f"Shape #{self.data.count}:\n"
            f"  Type: {self.data.shape_type}\n"
            f"  Position: ({self.data.x}, {self.data.y})\n"
            f"  Size: {shape_info}\n"
            f"  Color: rgb({self.data.r}, {self.data.g}, {self.data.b})\n"
            f"  Opacity: {self.data.opacity}"
        )
    
    def as_Part2_line(self) -> str:
        """as_Part2_line() method"""
        return f"{self.data.count:3d} {self.data.shape_type:3s} {self.data.x:3d} {self.data.y:3d} {self.data.radius:3d} {self.data.rx:3d} {self.data.ry:3d} {self.data.width:3d} {self.data.height:3d} {self.data.r:3d} {self.data.g:3d} {self.data.b:3d} {self.data.opacity:.2f}"
    
    def as_svg(self) -> str:
        """as_svg() method"""
        if self.data.shape_type == RandomShape.CIRCLE:
            return (
                f'<circle cx="{self.data.x}" cy="{self.data.y}" r="{self.data.radius}" '
                f'fill="rgb({self.data.r}, {self.data.g}, {self.data.b})" '
                f'opacity="{self.data.opacity}" />'
            )
        elif self.data.shape_type == RandomShape.RECTANGLE:
            return (
                f'<rect x="{self.data.x}" y="{self.data.y}" width="{self.data.width}" '
                f'height="{self.data.height}" fill="rgb({self.data.r}, {self.data.g}, {self.data.b})" '
                f'opacity="{self.data.opacity}" />'
            )
        else:  # ELLIPSE
            return (
                f'<ellipse cx="{self.data.x}" cy="{self.data.y}" rx="{self.data.rx}" '
                f'ry="{self.data.ry}" fill="rgb({self.data.r}, {self.data.g}, {self.data.b})" '
                f'opacity="{self.data.opacity}" />'
            )

def generate_random_shapes(num_shapes: int, config: Optional[PyArtConfig] = None) -> List[RandomShape]:
    """generate_random_shapes() function"""
    if config is None:
        config = PyArtConfig()
    
    shapes = []
    for i in range(1, num_shapes + 1):
        shapes.append(RandomShape(i, config))
    
    return shapes

def print_table_header() -> None:
    """print_table_header() function"""
    print(f"{'CNT':3s} {'SHA':3s} {'X':3s} {'Y':3s} {'RAD':3s} {'RX':3s} {'RY':3s} {'W':3s} {'H':3s} {'R':3s} {'G':3s} {'B':3s} {'OP':4s}")
    print("-" * 55)

def main() -> None:
    """main() function"""
    # Create a default art configuration
    config = PyArtConfig()
    
    # Generate 10 random shapes using the configuration
    shapes = generate_random_shapes(10, config)
    
    # Print the table header
    print_table_header()
    
    # Print each shape as a line in the table
    for shape in shapes:
        print(shape.as_Part2_line())

if __name__ == "__main__":
    main()