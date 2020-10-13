#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define TRUE 1
#define FALSE 0

void write_file();
void write_tlv(FILE *fp, int32_t id, int32_t len, char *body);
void write_int(FILE *fp, int32_t value);
void read_and_show_file(char *src_file_name);
int32_t buf_to_int(unsigned char buf[]);
void show_help();

// DEFAULT VALUES
char *file_name = "tlv_data.bin";
int   tlv_count = 1;
int   is_need_read_file = FALSE;
int   is_need_show_help = FALSE;

int main(int argc, char* argv[])
{                          
    if(argc > 1) {
        for(int i = 1; i < argc; i++) {
            if(strcmp(argv[i], "-n") == 0 && argc > i + 1) {                
               tlv_count = atoi(argv[i + 1]);
               i = i + 1;
            } else if(strcmp(argv[i], "-f") == 0 && argc > i + 1) {
               file_name = argv[i + 1];
               i = i + 1;
            } else if(strcmp(argv[i], "-r") == 0 && argc > i + 1) {
               is_need_read_file = TRUE;
               file_name = argv[i + 1];
            } else if(strcmp(argv[i], "-h") == 0) {
               is_need_show_help = TRUE;     
            }
        }
    }

    if(is_need_show_help) {
        show_help();
        return 0;
    }

    if (is_need_read_file == FALSE) {
        write_file();
    }

    if (is_need_read_file == TRUE) {
        read_and_show_file(file_name);
    }
 
    return 0;
}

void read_and_show_file(char *src_file_name) {
    int32_t r_id;
    char *r_body;
    int32_t r_len; 
    int read_bytes;
    int is_eof = FALSE;

    FILE *fp = fopen(src_file_name, "rb");
    while(is_eof != TRUE) {
        unsigned char buf[4];
        read_bytes = fread(buf, 4, 1, fp);
        if (read_bytes == 0) {
            is_eof = TRUE;
            continue;
        }

        r_id = buf_to_int(buf);
        read_bytes = fread(buf, 4, 1, fp);
        if (read_bytes == 0) {
            is_eof = TRUE;
            continue;
        }
        r_len = buf_to_int(buf);
        r_body = (char *) malloc(r_len);
        read_bytes = fread(r_body, r_len, 1, fp);     

        if (read_bytes == 0) {
            is_eof = TRUE;
            continue;
        }
        r_body[r_len] = '\0';
        printf("| \t%d \t| \t%d  \t| \t%s\n", r_id, r_len, r_body);
        free(r_body);
    }
    fclose(fp);
}

void write_file() {
    int32_t id = 1;
    char *prefix = "STR";
    char body[13]; // INT_MAX + "STR"
    FILE *fp;

    fp = fopen(file_name,"wb");
    for(int i = 0; i < tlv_count; i++) {
        sprintf(body, "%s%hd", prefix, id);
        write_tlv(fp, id, strlen(body), body);
        id++;
    }
    fclose(fp);
    printf("file %s successfully write !\n", file_name);
}

void write_tlv(FILE *fp, int32_t id, int32_t len, char *body) {
    write_int(fp, id);
    write_int(fp, len);
    fwrite(body, len, 1, fp);
}

void write_int(FILE *fp, int32_t value) {
    unsigned char bytes[4];
    bytes[0] = (value >> 24) & 0xFF;
    bytes[1] = (value >> 16) & 0xFF;
    bytes[2] = (value >> 8) & 0xFF;
    bytes[3] = value & 0xFF;
    for(int i = 0; i < 4; i++) {
        fwrite((const void*) & bytes[i], 1, 1, fp);
    }
}

int32_t buf_to_int(unsigned char buf[]) {
    int32_t value = (buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + buf[3];
    return value;
}

void show_help() {
    printf("usage: -r <filename> or -f <filename> -n <row_count>");
}