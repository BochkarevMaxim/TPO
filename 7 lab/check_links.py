import socket, urllib, lxml.html, sys
from urllib2 import Request, urlopen
from urlparse import urljoin

queuedURLs = []
checkedURLs = []
failed_pages = []
startUrl = ''

def check_pages (pages):
    try:
        for page_url in pages:
            code = urllib.urlopen(page_url).getcode()
            #print "{0} - {1}".format(page_url, code)
            if (code not in [200, 301]):
                failed_pages.append(page_url)
				
    except socket.error, e:
        print "Ping Error: ", e
		
			
def GetLinksFromPage(url, startUrl):
	req = Request(url)
	try: 
		response = urlopen(req)

	except BaseException, e:
		 return 0
		 
	else:
		page = response.read()
		try:
			doc = lxml.html.document_fromstring(page)
			
		except BaseException, e:
			return 

		else:
			for element, attribute, link, pos in doc.iterlinks():
				link = urljoin(url, link)

				if (not(link in checkedURLs) and not(link in queuedURLs) and ( -1 != link.find(startUrl, 0, len(link)))):
					queuedURLs.append(link)		
		
	finally:
		checkedURLs.append(url)
		del queuedURLs[0]	

def mainfunc(argv, startUrl):	
	
	if (len (sys.argv) == 1):
		startUrl = raw_input("No parameters. Please input URL: ")
	else:
		startUrl = argv[1]
	
	queuedURLs.append(startUrl)


	print ("Program start find all URLs at " + startUrl) 	
	while (len(queuedURLs)):
		if (not(queuedURLs[0] in checkedURLs)):
			GetLinksFromPage(queuedURLs[0], startUrl)
		else:
			del queuedURLs[0]

	print ("Program writes all URLs to file <URLs.txt>") 		
	f = open("URLs.txt", "w")
	for s in checkedURLs:
		f.write(s + '\n')
	f.close()
	print ("Program finished write correct URLs to file <URLs.txt>\n\n") 
	
	
	check_pages(checkedURLs)
	print ("Program writes broken URLs to file <BrokenURLs.txt>") 	
	f = open("BrokenURLs.txt", "w")
	for s in failed_pages:
		f.write(s + '\n')
	f.close()
	print ("Program finished write broken URLs to file <BrokenURLs.txt>\n\n") 
	
	print ("Program executed") 	
	
mainfunc(sys.argv, startUrl)
# http://bochtest.blogspot.ru/
