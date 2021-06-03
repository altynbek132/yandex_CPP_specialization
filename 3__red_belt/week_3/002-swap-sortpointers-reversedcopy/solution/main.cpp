
template <typename T>
void ReversedCopy(T* source, size_t count, T* destination) {
    auto source_begin = source;
    auto source_end = source + count;
    auto dest_begin = destination;
    auto dest_end = destination + count;
    if (source_end <= dest_begin || dest_end <= source_begin) {
        reverse_copy(source_begin, source_end, dest_begin);
    } else if (dest_begin > source_end) {
        /* Случай, когда целевая область лежит правее исходной
         * |   |   |   |d_6|d_5|d_4|d_3|d_2|d_1|
         * |s_1|s_2|s_3|s_4|s_5|s_6|   |   |   |
         * */
        size_t shift = dest_begin - source_begin;
        for (size_t i = 0; i < shift; ++i) {
            *(dest_end - 1 - i) = *(source_begin + i);
        }
        reverse(dest_begin, source_end);
    } else {
        /* Случай, когда целевая область лежит левее исходной
         * |d_6|d_5|d_4|d_3|d_2|d_1|   |   |   |
         * |   |   |   |s_1|s_2|s_3|s_4|s_5|s_6|
         * */

        // size_t shift = source_begin - dest_begin;
        // for (size_t i = 0; i < shift; ++i) {
        //     *(dest_begin + i) = *(source_end - 1 - i);
        // }

        for (size_t i = 0; source_end - i - 1 >= dest_end; ++i) {
            *(dest_begin + i) = *(source_end - i - 1);
        }
        reverse(source_begin, dest_end);
    }
}
