#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import cgi
import cgitb
import html

cgitb.enable()
form = cgi.FieldStorage()
text1 = form.getfirst("TEXT_1","")
text2 = form.getfirst("TEXT_2","")
text1 = html.escape(text1)
text2 = html.escape(text2)

print("Content-type: text/html\n")
print("""<!DOCTYPE HTML>
        <html>
        <head>
            <meta charset="utf-8">
            <title>Обработка данных форм</title>
        </head>
        <body>""")

print("<h1>Обработка данных форм!</h1>")
print("<p>TEXT_1: {0}</p>".format(text1))
print("<p>TEXT_2: {0}</p>".format(text2))

print("""</body>
        </html>""")
