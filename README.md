# libparse_dot

This library provides a parser for graphviz dot files.

**Dependencies**:

 - parse
   - common

## BUILD

```
mkdir project
cd project
git clone https://github.com/nbingham1/common.git
git clone -b old https://github.com/nbingham1/parse.git
git clone https://github.com/nbingham1/parse_dot.git
cd common
make
cd ../parse
make
cd ../parse_dot
make
cd ..
make
./test test.dot
```

## main.cpp

```
#include <common/standard.h>
#include <parse/parse.h>
#include <parse/default/block_comment.h>
#include <parse/default/line_comment.h>
#include <parse_dot/graph.h>

int main(int argc, char **argv)
{
	configuration config;
	config.set_working_directory(argv[0]);
	tokenizer tokens;
	parse_dot::graph::register_syntax(tokens);
	tokens.register_token<parse::block_comment>(false);
	tokens.register_token<parse::line_comment>(false);

	config.load(tokens, string(argv[1]), "");

	if (is_clean() && tokens.segments.size() > 0)
	{
		tokens.increment(false);
		tokens.expect<parse_dot::graph>();
		while (tokens.decrement(__FILE__, __LINE__))
		{
			parse_dot::graph syntax(tokens);
			
			if (is_clean())
				cout << syntax.to_string() << endl;

			tokens.increment(false);
			tokens.expect<parse_dot::graph>();
		}
	}

	complete();
	return is_clean();
}
```

## Makefile

```
CXX				= g++
CC				= gcc
CFLAGS			= -O2 -g -fmessage-length=0
INCLUDE_PATHS	= -Icommon -Iparse -Iparse_dot
LIBRARY_PATHS	= -Lcommon -Lparse -Lparse_dot
LIBRARIES		= -lparse_dot -lparse -lcommon
TARGET			= test

all: $(TARGET)

$(TARGET): main.o
	$(CXX) $(LIBRARY_PATHS) $(CFLAGS) main.o -o $(TARGET) $(LIBRARIES)

%.o: %.cpp 
	$(CXX) $(INCLUDE_PATHS) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o $(TARGET) $(TARGET).exe
```

## test.dot

```
digraph model
{
	subgraph wchb
	{
		graph["label"="" "variables"="R.r.t,R.r.f,R.e,L.r.t,L.r.f,L.e" "type"="local" "elaborate"="true" "reset"="~R.r.t&~R.r.f&R.e&~L.r.t&~L.r.f&L.e"];
		S0["shape"="circle" "width"="0.15" "peripheries"="2" "style"="filled" "fillcolor"="#000000" "label"=""];
		T0["shape"="plaintext" "label"="[ 1 ]"];
		S0->T0;
		S1["shape"="circle" "width"="0.25" "label"=""];
		T0->S1;
		T1["shape"="plaintext" "label"="[ R.e&L.r.t ]"];
		S1->T1;
		S2["shape"="circle" "width"="0.25" "label"=""];
		T1->S2;
		T2["shape"="plaintext" "label"="R.r.t"];
		S2->T2;
		T3["shape"="plaintext" "label"="[ R.e&L.r.f ]"];
		S1->T3;
		S3["shape"="circle" "width"="0.25" "label"=""];
		T3->S3;
		T4["shape"="plaintext" "label"="R.r.f"];
		S3->T4;
		S4["shape"="circle" "width"="0.25" "label"=""];
		T2->S4;
		T4->S4;
		T5["shape"="plaintext" "label"="~L.e"];
		S4->T5;
		S5["shape"="circle" "width"="0.25" "label"=""];
		T5->S5;
		T6["shape"="plaintext" "label"="[ ~R.e&~L.r.t&~L.r.f ]"];
		S5->T6;
		S6["shape"="circle" "width"="0.25" "label"=""];
		T6->S6;
		T7["shape"="plaintext" "label"="1"];
		S6->T7;
		S7["shape"="circle" "width"="0.25" "label"=""];
		T7->S7;
		T8["shape"="plaintext" "label"="~R.r.t"];
		S7->T8;
		S8["shape"="circle" "width"="0.25" "label"=""];
		T8->S8;
		S9["shape"="circle" "width"="0.25" "label"=""];
		T7->S9;
		T9["shape"="plaintext" "label"="~R.r.f"];
		S9->T9;
		S10["shape"="circle" "width"="0.25" "label"=""];
		T9->S10;
		T10["shape"="plaintext" "label"="1"];
		S8->T10;
		S10->T10;
		S11["shape"="circle" "width"="0.25" "label"=""];
		T10->S11;
		T11["shape"="plaintext" "label"="L.e"];
		S11->T11;
		T11->S0;
		T12["shape"="plaintext" "label"="[ 0 ]"];
		S0->T12;
		T12->S0;
	}
	subgraph environment
	{
		graph["label"="" "variables"="R.r.t,R.r.f,R.e,L.r.t,L.r.f,L.e" "type"="remote" "elaborate"="false" "reset"="~R.r.t&~R.r.f&R.e&~L.r.t&~L.r.f&L.e"];
		S12["shape"="circle" "width"="0.15" "peripheries"="2" "style"="filled" "fillcolor"="#000000" "label"=""];
		T13["shape"="plaintext" "label"="1"];
		S12->T13;
		S13["shape"="circle" "width"="0.25" "label"=""];
		T13->S13;
		T14["shape"="plaintext" "label"="[ 1 ]"];
		S13->T14;
		S14["shape"="circle" "width"="0.25" "label"=""];
		T14->S14;
		T15["shape"="plaintext" "label"="[ R.r.t|R.r.f ]"];
		S14->T15;
		S15["shape"="circle" "width"="0.25" "label"=""];
		T15->S15;
		T16["shape"="plaintext" "label"="~R.e"];
		S15->T16;
		S16["shape"="circle" "width"="0.25" "label"=""];
		T16->S16;
		T17["shape"="plaintext" "label"="[ ~R.r.t&~R.r.f ]"];
		S16->T17;
		S17["shape"="circle" "width"="0.25" "label"=""];
		T17->S17;
		T18["shape"="plaintext" "label"="R.e"];
		S17->T18;
		T18->S13;
		T19["shape"="plaintext" "label"="[ 0 ]"];
		S13->T19;
		S18["shape"="circle" "width"="0.25" "label"=""];
		T19->S18;
		S19["shape"="circle" "width"="0.25" "label"=""];
		T13->S19;
		T20["shape"="plaintext" "label"="[ 1 ]"];
		S19->T20;
		S20["shape"="circle" "width"="0.25" "label"=""];
		T20->S20;
		T21["shape"="plaintext" "label"="[ 1 ]"];
		S20->T21;
		S21["shape"="circle" "width"="0.25" "label"=""];
		T21->S21;
		T22["shape"="plaintext" "label"="L.r.t"];
		S21->T22;
		T23["shape"="plaintext" "label"="[ 1 ]"];
		S20->T23;
		S22["shape"="circle" "width"="0.25" "label"=""];
		T23->S22;
		T24["shape"="plaintext" "label"="L.r.f"];
		S22->T24;
		S23["shape"="circle" "width"="0.25" "label"=""];
		T22->S23;
		T24->S23;
		T25["shape"="plaintext" "label"="[ ~L.e ]"];
		S23->T25;
		S24["shape"="circle" "width"="0.25" "label"=""];
		T25->S24;
		T26["shape"="plaintext" "label"="1"];
		S24->T26;
		S25["shape"="circle" "width"="0.25" "label"=""];
		T26->S25;
		T27["shape"="plaintext" "label"="~L.r.t"];
		S25->T27;
		S26["shape"="circle" "width"="0.25" "label"=""];
		T27->S26;
		S27["shape"="circle" "width"="0.25" "label"=""];
		T26->S27;
		T28["shape"="plaintext" "label"="~L.r.f"];
		S27->T28;
		S28["shape"="circle" "width"="0.25" "label"=""];
		T28->S28;
		T29["shape"="plaintext" "label"="1"];
		S26->T29;
		S28->T29;
		S29["shape"="circle" "width"="0.25" "label"=""];
		T29->S29;
		T30["shape"="plaintext" "label"="[ L.e ]"];
		S29->T30;
		T30->S19;
		T31["shape"="plaintext" "label"="[ 0 ]"];
		S19->T31;
		S30["shape"="circle" "width"="0.25" "label"=""];
		T31->S30;
		T32["shape"="plaintext" "label"="1"];
		S18->T32;
		S30->T32;
		T32->S12;
	}
}
```

