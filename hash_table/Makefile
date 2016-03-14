
all:hash_table hash_table_bucket

hash_table:main.cpp
	g++ -o $@ $^ -D_SECOND_DETECT_ #-D_ONE_DETECT_

hash_table_bucket:main.cpp
	g++ -o $@ $^

.PHONY:clean
clean:
	rm -f hash_table hash_table_bucket
