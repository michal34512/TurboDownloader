# TurboDownloader
The main idea of this project was to create a portable tool which would help download videos from different streaming platforms 

TurboDownloader allows you to:
* Download regular files divided into multiple segments and then merge those segments together
* Download m3u8 videos and merging all .ts files together
* Selecting <b>cookies</b>, <b>headers</b> and <b>user agent</b> with which file will be downloaded

![obraz](https://github.com/michal34512/TurboDownloader/assets/136522993/e8e2d237-6735-4c11-bdaf-e570cce7080b)

# How to use it?
To download a file you need 3 things:
* <b>URL</b> of the video you want to download. In case of m3u8 video you need URL to whichever .ts file (ex. https://example.com/RANdoMhAsh/seg-52-v1-a1.ts) 
* <b>Header file</b> - file containing all headers needed to download file. You should name header files such as "header-exmaple.txt". Then it will be shown in the combo box for quick access.
* <b>Cookie file</b> - same as header file. In most cases servers don't require cookies for downloading a file so feel free to leave it blank

you can get <b>URL, headers and cookies</b> using Chrome DevTools or extensions

# Header & Cookie files - example
* <b>header file</b>  - This file contains additional information sent along with an HTTP request or response. HTTP headers provide important metadata about the request or response, such as the content type, authentication credentials, caching directives, and more
  </br>This is the example of how <b>header.txt</b> could look like:
```
# HTTP Header File

Accept: */*
Accept-Encoding: identity;q=1, *;q=0
Accept-Language: pl-PL,pl;q=0.8
Connection: keep-alive
Host: sl108.example.com
If-Range: "625691e3-536bf62"
Range: bytes=0-
Referer: https://www.example.com/
Sec-Ch-Ua: "Not.A/Brand";v="8", "Chromium";v="114", "Brave";v="114"
Sec-Ch-Ua-Mobile: ?0
Sec-Ch-Ua-Platform: "Windows"
Sec-Fetch-Dest: video
Sec-Fetch-Mode: no-cors
Sec-Fetch-Site: same-site
Sec-Gpc: 1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36
```
* <b>Cookie file</b> - This file contains all the cookies needed to make a request for the file. It is rarely needed and in most cases, just the <b>header.txt</b> file is sufficient.
  </br>This is the example of how <b>cookie.txt</b> file could look like:
```
# HTTP Cookie File

example.com    FALSE   /   FALSE   0   session_cookie   abcdef123456789
example.com    FALSE   /   FALSE   0   user_cookie      987654321abcdef
```

# Other settings
* <b>Single file size</b> - size of each segment being downloaded
* <b>Download rate</b> - number of segments which will be downloaded simultaneously. Some video hostings have limitation on transfer count (it's usually 3) per IP address. When you surpass this number download speed drops significantly.
* <b>Single file size</b> - size of each segment being downloaded
* <b>Prefix</b> - temporary files' filename prefix
* <b>Low speed limit</b> - Speed below which transfer is considered as slow and has to be restarted. For more info see https://curl.se/libcurl/c/CURLOPT_LOW_SPEED_LIMIT.html
* <b>Low speed time</b> - Time after which slow transfer is being restarted. For more info see https://curl.se/libcurl/c/CURLOPT_LOW_SPEED_TIME.html
* <b>Verbose</b> - Check this to see more info

