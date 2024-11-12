# libcgraph (Incidence-Type-RePair)

**Autor:** FR, EA

libcgraph is a C-library to compress and search in labeled graphs and labeled hypergraphs.

The library should run on Linux and macOS, it is not supported on Windows.

If you have questions regarding the implementation, feel free to contact adlerenno.

## Dependencies

- [libdivsufsort](https://github.com/y-256/libdivsufsort) to create the suffix-array
  - Using Homebrew
    - brew install libdivsufsort
  - Using bash:
    - git clone https://github.com/y-256/libdivsufsort.git
    - cd libdivsufsort
    - mkdir build
    - cd build
    - cmake -DCMAKE_BUILD_TYPE="Release" -DCMAKE_INSTALL_PREFIX="/usr/local" ..
    - make
    - sudo make install
    
- [serd](https://github.com/drobilla/serd) needed by the command-line-tool to read RDF-graphs
  - Using homebrew
    - brew install serd
  - Using apt-get
    - sudo apt-get install libserd-0-0

- [libmicrohttpd]() needed by the webservice for the server
  - Using homebrew
    - brew install libmicrohttpd
  - Using apt-get
    - sudo apt-get install libmicrohttpd-dev

## Build

To build, you need `cmake` and you can compile the library by:

```bash
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DOPTIMIZE_FOR_NATIVE=on -DWITH_RRR=on ..
make
```

The following parameters can be passed to CMake:

- `-DCMAKE_BUILD_TYPE=Release` activates compiler optimizations
- `-DOPTIMIZE_FOR_NATIVE=on` activates optimized processor functions, for example the more efficient `popcnt`-variants
- `-DNO_MMAP=on` read files using `read`-system-calls instead of `mmap`
- `-DWITH_RRR=on` activates the support for RRR bitsequences, but increases the library size significantly due to static tables. 
- `-DCLI=on` activates the compilation of the command-line-tool.
- `-DWEB_SERVICE=on` activates the compilation of the web-service. Needs the command-line-tool.

The library will be in the build-directory as "libcgraph.1.0.0.dylib" (macOS) or "libcgraph.so.1.0.0" (Linux).
The command-line-tool is in the build-directory as well and is called "cgraph-cli".

## Command-Line-Tool

With the command-line-tool "cgraph-cli" you can compress graphs and search within them.
The following help can also be obtained by `./cgraph-cli --help`.

```
Usage: cgraph-cli
    -h,--help                       show this help

 * to compress a RDF graph:
   cgraph-cli [options] [input] [output]
                       [input]          input file of the RDF graph
                       [output]         output file of the compressed graph

   optional options:
    -f,--format        [format]         format of the RDF graph; keep empty to auto detect the format
                                        possible values: "turtle", "ntriples", "nquads", "trig", "hyperedge"
       --overwrite                      overwrite if the output file exists
    -v,--verbose                        print advanced information

   options to influence the resulting size and the runtime to browse the graph (optional):
       --max-rank      [rank]           maximum rank of edges, set to 0 to remove limit (default: 12)
       --monograms                      enable the replacement of monograms
       --factor        [factor]         number of blocks of a bit sequence that are grouped into a superblock (default: 8)
       --sampling      [sampling]       sampling value of the dictionary; a value of 0 disables sampling (default: 32)
       --no-rle                         disable run-length encoding
       --no-table                       do not add an extra table to speed up the decompression of the neighborhood for an specific label
       --rrr                            use bitsequences based on R. Raman, V. Raman, and S. S. Rao [experimental]
                                        --factor can also be applied to this type of bit sequences


 * to read a compressed RDF graph:
   cgraph-cli [options] [input] [commands...]
                       [input]          input file of the compressed RDF graph

   optional options:
    -f,--format        [format]         default format for the RDF graph at the command `--decompress`
                                        possible values: "turtle", "ntriples", "nquads", "trig", "hyperedge"
       --overwrite                      overwrite if the output file exists, used with `--decompress`

   commands to read the compressed path:
       --decompress    [output]      decompresses the given compressed RDF graph
       --extract-node  [node-id]        extracts the node label of the given node id
       --extract-edge  [edge-id]        extracts the edge label of the given edge id
       --locate-node   [text]           determines the node id of the node with the given node label
       --locate-edge   [text]           determines the edge label id for the given text
       --locatep-node  [text]           determines the node ids that have labels starting with the given text
       --search-node   [text]           determines the node ids with labels containing the given text
       --hyperedges    [rank,label]*{,node}
                                        determines the edges with given rank. You can specify any number of nodes
                                        that will be checked the edge is connected to. The incidence-type is given 
                                        implicitly. The label must not be set, use ? otherwise. For example:
                                        - "4,2,?,3,?,4": determines all rank 4 edges with label 2 that are connected
                                           to the node 3 with connection-type 2 and node 4 with connection-type 4.
                                        - "2,?,?,5": determines all rank 2 edges any label that are connected
                                          to the node 5 with connection-type 1. In the sense of regular edges, 
                                          this asks for all incoming edges of node 5.
                                        Note that it is not allowed to pass no label and no nodes to this function.
                                        Use --decompress in this case.
       --node-count                     returns the number of nodes in the graph
       --edge-labels                    returns the number of different edge labels in the graph\n"
```

The command-line-tool allows via serd the Turtle, TriG, NTriples and NQuads formats for RDF-graphs. Additionally, there is a parser for hypergraphs. 
The formatting of a hypergraph file is one edge per line, 
each line starts with the label of the edge and is followed by the name of the nodes. 
The elements in a line can be separated by a white space or a tab. 
Note that the nodes are treated as named, 
so numbers would be inserted as names into the dictionary and the internally used numbers can differ.

## Library

To use Incidence-Type-RePair as a library, in the include folder is the corresponding header file with the methods supported by the library.
