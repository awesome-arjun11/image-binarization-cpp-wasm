# image-binarization-cpp-wasm

Image binarization using otsu's method on HTML [ImageData](https://developer.mozilla.org/en-US/docs/Web/API/ImageData) in c++, compiled to WASM for the web.

- - - -

## See In action: [Web Demo](https://awesome-arjun11.github.io/image-binarization-cpp-wasm)
* **note:** Demo loads the .wasm file without the glue code. 

- - - -

## Build

* Requires [Emscripten](https://github.com/emscripten-core/emscripten).

```sh
$ em++ img_processing.cpp -s ALLOW_MEMORY_GROWTH=1 -s STANDALONE_WASM -s EXPORTED_FUNCTIONS="['_otsuBinarize', '_malloc', '_free']" -Os -o img_processing.wasm
```

- - - -

### Note: when loading wasm with [WebAssembly.instantiateStreaming](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/WebAssembly/instantiateStreaming) on a local test server
* The server must be configured to serve the .wasm file with the correct MIME type by sending the **Content-Type: application/wasm** header
* **Example:** configured python http.server script:
```python
import http.server, socketserver

PORT = 8000
Handler = http.server.SimpleHTTPRequestHandler

Handler.extensions_map['.wasm'] = 'application/wasm'

with socketserver.TCPServer(("", PORT), Handler) as httpd:
    print("serving at port", PORT)
    httpd.serve_forever()
```

- - - -

### References
- [Otsu thresholding — image binarization](https://medium.com/@hbyacademic/otsu-thresholding-4337710dc519) by HBY coding academic
- [otsu's method Wikipedia](https://en.wikipedia.org/wiki/Otsu%27s_method#Otsu's_method)
- [Loading WebAssembly modules efficiently](https://developers.google.com/web/updates/2018/04/loading-wasm)
