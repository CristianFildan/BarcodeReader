import cv2 
from pyzbar.pyzbar import decode
import time
from csv import excel
import pandas as pd
import numpy as np
from openpyxl import load_workbook
import math
from tkinter import Tk, Button


camera = cv2.VideoCapture(0, cv2.CAP_DSHOW)
excel_file = 'reduced_database.xlsx'
df = pd.read_excel(excel_file)



            
        

#import the useful columns from the excel


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

##########GETTING BARCODE###################
while(True):
    #pull the camera's current frame in frame
    global barcode
    flag = 0
    ret, frame = camera.read()
    #show it on the screen ( for easier scanning )
    cv2.imshow('frame',frame)
    #pyzbar is able to detect multiple barcodes frm the same frame
    for barcodes in decode(frame):
        #get the barcode value and save it as a string
        barcode = str(barcodes.data)
        #fix the string so you only have the code xxx...x and not b"xxx...x"
        barcode = barcode[2:len(barcode)-1]
        print(barcode)
        flag = 1


    #if q is entered break the program
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    if flag:
        break


######POST GETTING BARCODE#################
global code, material_type, material_position_index
condition = df['code'] == barcode

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
    df.at[code_position_index] = barcode
    print("Code not detected")
    set_material_to_input()


elif not material_type : 
    print("Material not detected")
    set_material_to_input()

print(code_position_index,code,material_type)
camera.release()
cv2.destroyAllWindows()

#print(code, material_type, type(material_type), code_position_index)
