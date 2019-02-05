#!/usr/bin/env python

# WriteSharedFormula.py

# Installation: pip install XlsXcessive
# https://pypi.org/project/XlsXcessive/

import io

from xlsxcessive import xlsx
from xlsxcessive.worksheet import Cell

def main():
	workbook = xlsx.Workbook()
	sheet1 = workbook.new_sheet('Sheet 1')
	sheet1.cell('B1', value=7)
	sheet1.cell('C1', value=8)
	sheet1.cell('D1', value=9)
	formula = sheet1.formula('B1 + C1', shared=True)
	sheet1.cell('D2', formula) # master
	sheet1.cell('E2', formula) # shared, references the master formula	
	xlsx.save(workbook, 'test.xlsx') # save local file

if __name__ == "__main__":
    # execute only if run as a script
    main()
