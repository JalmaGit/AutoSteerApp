from tkinter import *
import tkintermapview

def left_click_event(coords):
    print("Add marker:", coords)
    marker = mapWidget.set_marker(coords[0], coords[1], text="new marker")

root = Tk()
root.geometry("1920x1080")
root.title("Auto Steer")
#Make app Resizable
root.resizable(True,True)

label = Label(root,text="Auto Steer", font=("Helvetica",32))
label.pack(pady=10)
#label.pack(padx=50)

myLabel = LabelFrame(root)
myLabel.pack(pady=50)
    
mapWidget = tkintermapview.TkinterMapView(myLabel,width=1000,height=800)
mapWidget.set_tile_server("https://services.arcgisonline.com/arcgis/rest/services/World_Imagery/MapServer/tile/{z}/{y}/{x}")
mapWidget.set_position(59.22467, 10.33620)
mapWidget.set_zoom(15)

mapWidget.add_left_click_map_command(left_click_event)


mapWidget.pack()

root.mainloop()

print()