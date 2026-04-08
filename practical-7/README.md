# DAA Practical 7

```
/**
 * Just some space for thinking out aloud
 *
 * Each Graph is a generic. It takes in one type parameter: the RecordType which denotes a datatype which implements the Record abstract class.
 *      The Record abstract class is supposed to have a display function that all derived classes must override
 *
 *      The <data/StudentRecord> is one such class that implements Record. The parser is tightly coupled with this implementation, because it has to read data into its fields.
 *
 * In io.hpp, we have a function Graph<Record> parseGraph(edgelist_path, satellite_path) that parses files into a Graph representation
 *
 * You form a graph by adding nodes to it one at a time using the addNode function.
 * A Node is tightly coupled with the Graph class, but it is not tightly coupled with the Record implementation. The Record implementation shows the
 */
```
