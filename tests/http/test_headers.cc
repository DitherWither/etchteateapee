#include <gtest/gtest.h>
#include <sstream>

extern "C" {
#include <etch.h>
}

TEST(HTTPHeadersTest, TestHeaderToString)
{
        EtchHeader header = etch_header_new("Content-Length", "100");
        char *str = etch_header_to_string(header);

        ASSERT_STREQ(str, "Content-Length: 100\r\n");
        etch_header_free(header);
}

TEST(HTTPHeadersTest, TestHeadersToString)
{
        EtchHeader *headers = (EtchHeader *)malloc(sizeof(EtchHeader) * 4);
        headers[0] = etch_header_new("Connection", "close");
        headers[1] =
                etch_header_new("Content-Type", "text/html; charset=utf-8");
        headers[2] = etch_header_new("Content-Language", "en-US");
        headers[3] = etch_header_new("X-Test-Header", "hewo there");

        const char *body = "123456789";

        char *headers_str = etch_headers_to_string(headers, 4, body);

        std::stringstream ss{};
        ss << "Content-Length: 9\r\n"
           << "Connection: close\r\n"
           << "Content-Type: text/html; charset=utf-8\r\n"
           << "Content-Language: en-US\r\n"
           << "X-Test-Header: hewo there\r\n"
           << "\r\n";

        ASSERT_STREQ(ss.str().c_str(), headers_str);
        etch_headers_free(headers, 4);
}

TEST(HTTPHeadersTest, TestStringToHeader)
{
        EtchHeader header;
        size_t bytes_read;

        // Test case where header has a body
        const char *with_body =
                "Content-Type: text/html; charset=utf-8\r\n\r\nHello, World\r\n";

        bytes_read = etch_header_from_string(with_body, &header);

        ASSERT_STREQ(header.name, "Content-Type");
        ASSERT_STREQ(header.value, "text/html; charset=utf-8");
        ASSERT_EQ(bytes_read, 42);

        etch_header_free(header);

        // Case where there is no body
        const char *without_body = "X-Name: foo bar\r\n";

        bytes_read = etch_header_from_string(without_body, &header);

        ASSERT_STREQ(header.name, "X-Name");
        ASSERT_STREQ(header.value, "foo bar");
        ASSERT_EQ(bytes_read, 17);

        etch_header_free(header);

        // Case where no newline
        const char *without_newline = "Connection: close";

        bytes_read = etch_header_from_string(without_newline, &header);

        ASSERT_STREQ(header.name, "Connection");
        ASSERT_STREQ(header.value, "close");
        ASSERT_EQ(bytes_read, 17);

        etch_header_free(header);

        // Error cases
        const char *null_at_start = "\0";
        bytes_read = etch_header_from_string(null_at_start, &header);
        ASSERT_EQ(bytes_read, -1);
        etch_header_free(header);

        const char *newline_at_start = "\r\nhello";
        bytes_read = etch_header_from_string(newline_at_start, &header);
        ASSERT_EQ(bytes_read, -1);
        etch_header_free(header);

        const char *no_colon = "Hello, World!\r\n";
        bytes_read = etch_header_from_string(no_colon, &header);
        ASSERT_EQ(bytes_read, -1);
        etch_header_free(header);
}