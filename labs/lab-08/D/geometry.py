import math

# Fill your boots here...

class Point:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y
    
    def __repr__(self):
        return f"Point({self.x}, {self.y})"
    
    def delta_x(self, dx):
        return Point(self.x + dx, self.y)
    
    def delta_y(self, dy):
        return Point(self.x, self.y + dy)
    
    def translate(self, dx, dy):
        return Point(self.x + dx, self.y + dy)

class Circle:
    def __init__(self, center, radius):
        self.center = center
        self.radius = radius
    
    def __repr__(self):
        return f"Circle({self.center}, {self.radius})"
    
    def translate(self, dx, dy):
        return Circle(self.center.translate(dx, dy), self.radius)
    
    def perimeter(self):
        return 2 * math.pi * self.radius
    
    def area(self):
        return math.pi * self.radius * self.radius

class Rectangle:
    def __init__(self, upper_left, lower_right):
        self.upper_left = upper_left
        self.lower_right = lower_right
    
    def __repr__(self):
        return f"Rectangle({self.upper_left}, {self.lower_right})"
    
    def area(self):
        width = abs(self.upper_left.x - self.lower_right.x)
        height = abs(self.upper_left.y - self.lower_right.y)
        return width * height
    
    def perimeter(self):
        width = abs(self.upper_left.x - self.lower_right.x)
        height = abs(self.upper_left.y - self.lower_right.y)
        return 2 * (width + height)
    
    def translate(self, dx, dy):
        return Rectangle(
            self.upper_left.translate(dx, dy),
            self.lower_right.translate(dx, dy)
        )
