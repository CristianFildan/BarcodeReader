import pandas as pd


excel_file = 'openfoodfacts_export.xlsx'


df = pd.read_excel(excel_file, usecols = ['code','packaging'])


df.to_excel('reduced_database.xlsx', index = False)