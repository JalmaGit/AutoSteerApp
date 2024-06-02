from tkinter import *
import tkintermapview

class AutoSteerMapApp:
    def __init__(self, root):
        self.root = root
        self.root.geometry("1920x1080")
        self.root.title("Auto Steer")
        self.root.resizable(True, True)

        label = Label(self.root, text="Auto Steer", font=("Helvetica", 32))
        label.pack(pady=10)

        self.myLabel = LabelFrame(self.root)
        self.myLabel.pack(pady=50)

        self.mapWidget = tkintermapview.TkinterMapView(self.myLabel, width=1000, height=800)
        self.mapWidget.set_tile_server("https://services.arcgisonline.com/arcgis/rest/services/World_Imagery/MapServer/tile/{z}/{y}/{x}")
        self.mapWidget.set_position(59.22467, 10.33620)
        self.mapWidget.set_zoom(15)

        self.mapWidget.add_left_click_map_command(self.left_click_event)
        self.mapWidget.add_right_click_menu_command(label="Add Marker", command=self.add_marker_event, pass_coords=True)
        self.mapWidget.pack()

        self.drawing_enabled = BooleanVar()
        self.drawing_enabled.set(False)

        self.drawing = False
        self.current_line = None
        self.dragging = False

        self.checkbox = Checkbutton(self.root, text="Enable Drawing", variable=self.drawing_enabled, command=self.toggle_drawing)
        self.checkbox.pack(pady=10)

        self.mapWidget.canvas.bind("<Button-1>", self.start_drawing)
        self.mapWidget.canvas.bind("<B1-Motion>", self.draw)
        self.mapWidget.canvas.bind("<ButtonRelease-1>", self.stop_drawing)

    def left_click_event(self, coords):
        print("Add marker:", coords)
        marker = self.mapWidget.set_marker(coords[0], coords[1], text="new marker")

    def add_marker_event(self, coords):
        print("Delete marker:", coords)
        new_marker = self.mapWidget.set_marker(coords[0], coords[1], text="new marker")

    def toggle_drawing(self):
        if self.drawing_enabled.get():
            self.mapWidget.canvas.bind("<Button-1>", self.start_drawing)
            self.mapWidget.canvas.bind("<B1-Motion>", self.draw)
            self.mapWidget.canvas.bind("<ButtonRelease-1>", self.stop_drawing)
        else:
            self.mapWidget.canvas.unbind("<Button-1>")
            self.mapWidget.canvas.unbind("<B1-Motion>")
            self.mapWidget.canvas.unbind("<ButtonRelease-1>")
            self.mapWidget.canvas.bind("<ButtonPress-1>", self.start_drag)
            self.mapWidget.canvas.bind("<B1-Motion>", self.drag)
            self.mapWidget.canvas.bind("<ButtonRelease-1>", self.stop_drag)

    def start_drawing(self, event):
        self.drawing = True
        self.start_x, self.start_y = event.x, event.y
        self.current_line = self.mapWidget.canvas.create_line(event.x, event.y, event.x, event.y, fill='blue')

    def start_drag(self, event):
        self.dragging = True
        self.mapWidget.canvas.scan_mark(event.x, event.y)

    def draw(self, event):
        if self.drawing:
            self.mapWidget.canvas.coords(self.current_line, self.start_x, self.start_y, event.x, event.y)

    def stop_drawing(self, event):
        self.drawing = False
        self.current_line = None

    def drag(self, event):
        if self.dragging:
            self.mapWidget.canvas.scan_dragto(event.x, event.y, gain=1)

    def stop_drag(self, event):
        self.dragging = False

if __name__ == "__main__":
    root = Tk()
    app = AutoSteerMapApp(root)
    root.mainloop()
    print("Exited Successfully")