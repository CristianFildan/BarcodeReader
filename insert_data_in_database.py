import cv2 
from pyzbar.pyzbar import decode
import time
from csv import excel
import pandas as pd
import numpy as np
from openpyxl import load_workbook
import math
from tkinter import Tk, Button
proxy_code = 2255

excel_file = 'reduced_database.xlsx'

#import the useful columns from the excel
df = pd.read_excel(excel_file)

condition = df['code'] == proxy_code

#################################BUTTONS####################################

variable = ""
def make_something(value):
    global variable
    variable = value
    df.at[code_position_index,'packaging'] = variable
    df.to_excel('reduced_database.xlsx', index = False)
    exit()


def set_material_to_input():
    root = Tk()
    Plastic_Button = Button(root, text='Plastic',command=lambda *args: make_something("Plastic")).pack()
    Glass_Button = Button(root, text='Glass',command=lambda *args: make_something("Glas")).pack()
    Organic_Waste_Button  = Button(root, text='Organic Waste',command=lambda *args: make_something("Organic")).pack()
    Cardboard_Button  = Button(root, text='Cardboard',command=lambda *args: make_something("Cardboard")).pack()
    Not_Recyclable_Button = Button(root, text='Not Recyclable',command=lambda *args: make_something("Not Recyclable")).pack()
    root.mainloop()



#################################BUTTONS####################################

global code, material_type, material_position_index

try:
    code = df.loc[condition]['code'].values[0]
    material_type = df.loc[condition]['packaging'].values[0]
    code_position_index = df[condition].index.values[0]
except:
    code = None
    material_type = None
    code_position_index = None


if not code:
    code_position_index = df.index[-1]+1
    print(df.index[-1]+1)
    df.at[code_position_index] = proxy_code
    set_material_to_input()

elif math.isnan(material_type) or not material_type : 
    set_material_to_input()




#print(code, material_type, type(material_type), code_position_index)
