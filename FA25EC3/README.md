# Project: Text Based RPG using Templates, Dynamic Trees, and OpenAI

This project combines data structures, templates, file processing, and an external API. You will build a fully dynamic, templated tree structure that stores a choose your own adventure style narrative. The story is generated automatically using OpenAI and saved into a text file. Your program will parse that file and assemble the story tree. After the tree is constructed, you will later support simple gameplay.

## What You Are Given

Your starter code includes:

1. `main.cpp`
2. `tree.h`
3. `CMakeLists.txt` (provided separately)
4. A `story.txt` file that will be created automatically the first time you run the program

`main.cpp` already performs the following:
1. It prompts the user for an OpenAI API key.
2. It calls OpenAI using a curl command.
3. It saves the response to `story.txt`.
4. It parses `story.txt` into a list of raw story nodes.
5. It calls placeholder functions in your tree class to build a dynamic story tree.

Your job is to implement the entire tree class in `tree.h` and any supporting `.tpp` file you may create.

## Story Format

The OpenAI output must follow this strict structure:

```
[1] TEXT: You stand in a forest clearing. NEXT: 2, 3
[2] TEXT: You follow a narrow path. NEXT: 4
[3] TEXT: You enter a dark cave. NEXT: 4, 5
[4] TEXT: You find an abandoned hut. NEXT: 6
[5] TEXT: A river blocks your way. NEXT: 6
[6] TEXT: You reach the ancient ruins. NEXT:
```

Each line must include:
- A bracketed node ID  
- A TEXT field  
- A NEXT field containing a comma separated list of children, if any

The parser in `main.cpp` depends on this format.

## What You Must Build

### Template Tree Class

You are responsible for building a templated tree where:
- Each node stores an ID and data
- A node may have multiple parents
- A node may have multiple children
- A child may appear under many parent nodes
- All node memory must be dynamically allocated
- You must prevent memory leaks

### Required Methods

Implement these methods in your tree class:

```
createRoot(id, value)
addNode(parentID, childID, value)
findNode(id)
printAll()
~Tree()
```

You may add additional helper functions as needed.

## How main.cpp Uses Your Code

When the program runs:

1. The user enters their OpenAI API key.
2. The program calls OpenAI and writes the story to `story.txt`.
3. The story text is parsed into a vector of raw nodes.
4. You will:
   - Call `createRoot` using the first story node  
   - Call `addNode` to connect all remaining nodes  
5. You will print the tree or support navigation later

## Output Guide

### Expected Console Flow

```
Enter your OpenAI API key:
Fetching story from OpenAI...
Story loaded into your dynamic tree structure.
Implement the Tree class to enable traversal and printing.
```

Once your tree implementation is complete, printing it might look like:

```
Node 1: You stand in a forest clearing
  Child -> 2
  Child -> 3
Node 2: You follow a narrow path
  Child -> 4
Node 3: You enter a dark cave
  Child -> 4
  Child -> 5
...
```

## Examples of Valid and Invalid Paths

### Valid Path Example
If node 1 connects to node 2, and node 2 connects to node 4, then the path:

```
1 → 2 → 4
```

is valid.

### Invalid Path Example
If node 3 does not list node 7 as a child, then the path:

```
3 → 7
```

is not valid.

## Your Goal

You are building a dynamic, linked, templated tree that represents a branching adventure story. It must support nodes with multiple parents and children, and it must be fully implemented using pointers and dynamic allocation.

Good luck, and test every pointer and every connection carefully.

## Full Output Guide (Consolidated)

When the entire project is implemented correctly, the program will follow this sequence:

1. Prompt the user for their OpenAI API key.
2. Use curl to request a structured adventure story from OpenAI.
3. Save the response to `story.txt`.
4. Parse every line of the story into node IDs, story text, and child relationships.
5. Build a fully dynamic tree using your templated `Tree` and `Node` classes.
6. Print the entire tree in a readable format.

A complete example of expected structure:

```
[1] TEXT: You stand in a forest clearing. NEXT: 2, 3
[2] TEXT: You follow a narrow path. NEXT: 4
[3] TEXT: You enter a dark cave. NEXT: 4, 5
[4] TEXT: You find an abandoned hut. NEXT: 6
[5] TEXT: A river blocks your way. NEXT: 6
[6] TEXT: You reach the ancient ruins. NEXT:
```

Your printed output (once your tree is implemented) should follow a format similar to:

```
Node 1: You stand in a forest clearing
  Child -> 2
  Child -> 3

Node 2: You follow a narrow path
  Child -> 4

Node 3: You enter a dark cave
  Child -> 4
  Child -> 5

Node 4: You find an abandoned hut
  Child -> 6

Node 5: A river blocks your way
  Child -> 6

Node 6: You reach the ancient ruins
  Child -> (none)
```


## Sample Output Run Through

Below is an example of what a complete program run might look like once your `Tree` and `Node` implementations are finished. This demonstrates the full flow from API call through tree construction and printing.

```
Enter your OpenAI API key:
sk-abc123...

Fetching story from OpenAI...
Story loaded into your dynamic tree structure.

===== Story Tree =====
Node 1: You stand in a forest clearing
  Child -> 2
  Child -> 3

Node 2: You follow a narrow path
  Child -> 4

Node 3: You enter a dark cave
  Child -> 4
  Child -> 5

Node 4: You find an abandoned hut
  Child -> 6

Node 5: A river blocks your way
  Child -> 6

Node 6: You reach the ancient ruins
  Child -> (none)
======================
```

This run through shows the exact formatting your print function should aim for, although the story text itself will vary because it is generated by OpenAI each time the program runs.


## Sample Gameplay Run Through

Below is an example of what gameplay might look like once you implement `playGame()` in your `Tree` class. The story text will vary because it is generated by OpenAI, but the interaction flow should match this format.

```
===== Begin Adventure =====

You stand in a forest clearing.
Choose your next action:
1. Follow the narrow path
2. Enter the dark cave
Selection: 1

You follow a narrow path.
Choose your next action:
1. Approach the abandoned hut
Selection: 1

You find an abandoned hut.
Choose your next action:
1. Continue toward the ruins
Selection: 1

You reach the ancient ruins.
There are no further paths.
Your journey ends here.

===== Adventure Complete =====
```

This example demonstrates:
1. Displaying the current node’s text.  
2. Showing numbered options for all children.  
3. Accepting user input and validating it.  
4. Moving to the selected child node.  
5. Stopping when a node has no children.  

Your `playGame()` implementation must follow this structure closely for a consistent user experience.