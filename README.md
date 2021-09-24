turing-machine
==============
This repository contains simple Turing Machine compiler written in C++.

# Language definition
The Compiler uses custom language defined by the BNF below.
```
<TM> ::= <header>* <body>

<header> ::= <name> : <name>

<body> ::= "{" <rule>* "}"
<rule> ::= <state> <rule-body>
    | <state> "{" <rule-body>* "}"
<rule-body> ::= <symbols> <direction> <optional-state> <optional-symbols>
<symbols> ::= <symbol> | "{" <symbol>* "}"
<optional-symbols> ::= <symbol> | "{" <optional-symbol>* "}"
<optional-symbol> ::= <symbol> | "-"
<optional-state> ::= <state> | "-"
<state> ::= <name>
<direction> ::= "<" | ">" | "-"
```
