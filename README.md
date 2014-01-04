# SipHashSum

This application provides a sha1sum (or md5sum)-like tool using the siphash24 algorithm. 

It can be used as a fast alternative for indexing files to sha1 or md5. 
The output is limited to 64bits and the algorithm is not cryptographicly secure.

Original siphash code from https://github.com/emboss/siphash-c