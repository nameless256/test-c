SECTIONS
{
    .meta_type_data : ALIGN(4)
    {
        __meta_type_data_start = .;
        KEEP(*(.meta_type_data))
        __meta_type_data_end = .;
    }
}
INSERT AFTER .data;