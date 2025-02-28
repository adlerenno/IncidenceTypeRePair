/**
 * @file constants.h
 * @author FR
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

// Default maximum rank of RePair
#define DEFAULT_MAX_RANK 128
#define LIMIT_MAX_RANK 128

// Default paramer if monograms should be replaced
#define DEFAULT_MONOGRAMS (false)

// Default factor for bitsequences
#define DEFAULT_FACTOR 64

// Default sampling value for the dictionary
#define DEFAULT_SAMPLING 0

// Default parameter if the Run-Length-Encoding is used
#define DEFAULT_RLE (true)

// Default parameter if the NT table should be added
#define DEFAULT_NT_TABLE (true)

#ifdef RRR
// Default value of bitsequences of type RRR are used
#define DEFAULT_RRR (false)
#endif

#ifdef WEB_SERVICE
// Default Port for Web Service
#define DEFAULT_PORT 8080
#define DEFAULT_QUIT_SERVER_CHAR ('q')
#endif

// SPARQL Whitespace Characters. Only ' ' would allow parsing form command line.
#define SPARQL_WHITESPACE_CHARS (" \t\n_")

// Magic number of the compressed graph file
#define MAGIC_GRAPH "CGRAPH1\x00"
#define MAGIC_GRAPH_LEN (strlen(MAGIC_GRAPH) + 1)

// Magic byte for regular bit sequences
#define BITSEQUENCE_REGULAR 0x1

// Magic byte for bit sequences from paper "Practical Implementation of Rank and Select Queries"
#define BITSEQUENCE_RG 0x2

#ifdef RRR
// Magic byte for bit sequences from paper "Succinct Indexable Dictionaries with Applications to Encoding k-ary Trees, Prefix Sums and Multisets"
#define BITSEQUENCE_RRR 0x3
#endif

#endif
