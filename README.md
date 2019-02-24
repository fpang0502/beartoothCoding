#**Beartooth Coding Sample: Manchester Coder**

This is a Manchester Parser that takes an input text file and encodes or decodes using Manchester code.

**encodeInput.txt** 
	Contains the information to be encoded

**encodeOutput.txt** 
	Contains the encoded information in Manchester format

**decodeOutput.txt** 
	Contains the decoded data from encodeOutput.txt

**To run:**

**Decode Mode:**
	./main -d inputfile outputfile

**Encode Mode:**
	./main -e inputfile outputfile

**What I ran:**

	./main -e encodeInput.txt encodeOutput.txt

	./main -d encodeOutput.txt decodeOutput.txt