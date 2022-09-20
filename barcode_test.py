#imports
import cv2 
from pyzbar.pyzbar import decode
import time
from csv import excel
import pandas as pd
import numpy as np


#turn on the camera
camera = cv2.VideoCapture(1, cv2.CAP_DSHOW)

#database filepath
excel_file = 'openfoodfacts_export.xlsx'

#import the useful columns from the excel
df = pd.read_excel(excel_file, usecols = ['code', 'product_name_en','packaging'])

while(True):
    #pull the camera's current frame in frame
    ret, frame = camera.read()
    #show it on the screen ( for easier scanning )
    cv2.imshow('frame',frame)
    #pyzbar is able to detect multiple barcodes frm the same frame
    for code in decode(frame):
        #get the barcode value and save it as a string
        barcode = str(code.data)
        #fix the string so you only have the code xxx...x and not b"xxx...x"
        barcode = barcode[2:len(barcode)-1]
        print(barcode)
        try:
            code_material_type = df.loc[df['code'] == barcode]['packaging'].values[0]
        except IndexError:
            print(("This product is not in the database."))
            new_product_material = input("Introduce the main maaterial:")
        
    time.sleep(0.2)
    #if q is entered break the program
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

#turn off the camera
camera.release()
# Destroy all the windows
cv2.destroyAllWindows()