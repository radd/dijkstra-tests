# dijkstra-tests

Testing the performance of a programming language based on the Dijkstra's Algorithm.

Dijkstra's Algorithm is an algorithm for finding the shortest paths between two nodes in a graph. In this project, the algorithm has been modified to find shortest paths between all nodes in a graph. This provides higher CPU load, so it's easier to test language performance.

### Programming languages:

- C
- C++
- C#
- Java
- JavaScript (Node.js)
- Python (PyPy3)

### Graphs:

4 types of graphs have been created for this project:

- 10 nodes
- 100 nodes
- 200 nodes
- 300 nodes

#### Example:
200 nodes

<img src="https://radd.github.io/other/images/dijkstra/1.png" width="600" >

[See graph online](https://graphonline.ru/en/?graph=mwGnsEwHTCYRYMcl)

## Build

Open specific language folder, go to build and execute cmd.bat file

```bash
cd java
cd build
.\cmd.bat
```

## Run all tests with specific nodes

```bash
.\testResult.ps1 $size $from $to
```

Where:
- $size is graph size
- $from is start node
- $to is end node

## Run all tests

```bash
.\runAllTests.ps1 $size
```

Where:
- $size is graph size

## Output

Test results are saved to **output.txt** file


### Example for Java:

```bash
01 June 2018 10:57:44
---------------------- J A V A ------------------------
Graf 100
313
328
313
328
312

Graf 200
4016
4141
5890
3829
4594

Graf 300
23750
24188
21532
24563
21563
```