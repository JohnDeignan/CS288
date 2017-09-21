from __future__ import print_function
from datetime import date, datetime, timedelta
import xml.dom.minidom
import mysql.connector
import subprocess
import glob
import schedule
import time

def getDataText(nodelist):
    for node in nodelist:
        if node.nodeType == node.TEXT_NODE:
            if any((n in nums) for n in node.data):
                dat.append(node.data)

def getNameText(nodelist):
    for node in nodelist:
        if node.nodeType == node.TEXT_NODE:
            if any((p in paren) for p in node.data):
                names.append(node.data)

def getData(doc):
    text = doc.getElementsByTagName("td")
    for element in text:
        getDataText(element.childNodes)

def getName(doc):
    text = doc.getElementsByTagName("a")
    for element in text:
            getNameText(element.childNodes)


getName(dom)
getData(dom)

schedule.every(10).minutes.do(run)

def run():
	subprocess.check_output('cdate=`date + %Y_%M_%d_%H_%m_%S', shell=True)
	subprocess.check_output('0 */1 * * * /usr/bin/wget -O "Documents/CS288/HW9/nyse_${cdate}.html" "http://online.wsj.com/mdc/public/page/2_3021-activnyse-actives.html"', shell=True)
	subprocess.check_output('java -jar tagsoup-1.2.jar <' + newest + '> nysex.xtml', shell=True)
	files = [x for x in os.listdir('Documents/CS288/HW10') if x.endswith(".xhtml")]
	newest = max(files , key = os.path.getctime)
	delete = "DELETE FROM STOCKS"
	cnx = mysql.connector.connect(user='root', password='password', database='stocks')
	cursor = cnx.cursor()
	cursor.execute(delete)
	dom = xml.dom.minidom.parse("C:\\Users\\Johnnys\\Documents\\HW9\\" + newest)
	nums = set('0123456789')
	paren = set('()')
	dat = []
	names = []
	indx = []
	volume = []
	price = []
	chg = []
	chgpercent = []
	a=0
	b=0
	c=0
	d=0
	e=0
	i=0
	for y in names:
    		for x in range(len(dat)):
        		indx.append(dat[i])
        		a+=1
        		i+=1
        		volume.append(dat[i])
        		b+=1
        		i+=1
        		price.append(dat[i])
        		c+=1
        		i+=1
        		chg.append(dat[i])
        		d+=1
        			i+=1
        		chgpercent.append(dat[i])
        		e+=1
        		i+=1        
        		z=y.split("(")
        		name=z[0]
        		symbol=z[1][:len(z[1])-2]
        		add_stock = ("INSERT INTO STOCKS (COMPANY, SYMBOL, INDX, VOLUME, PRICE, CHG, CHGPERCENT)"
        		        " VALUES (%s, %s, %s, %s, %s, %s, %s)")
       		 total = (name, symbol, indx[a-1], volume[b-1], price[c-1], chg[d-1], chgpercent[e-1])
        		cursor.execute(add_stock, total)
       		 cnx.commit()
        		break

	cnx.close()





