# RMQ implementations + Benchmark

Compares [Binary Indexed Trees](http://www.ioinformatics.org/oi/pdf/v9_2015_39_44.pdf) with a Bottum-Up and Top-Down version of the Segment (Range) Tree. 

## Results

Using Intel® Core™ i7-4600M Processor, elementary OS 0.4 Loki, gcc 5.4.1

    QUERY BENCHMARK
    BIT:   0.289190s
    ST_BU: 0.862481s
    ST_TD: 2.401687s

    UPDATE BENCHMARK
    BIT:   0.333717s
    ST_BU: 0.202036s
    ST_TD: 1.150674s
