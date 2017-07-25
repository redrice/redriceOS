struct console_dev {
	unsigned int curx;
	unsigned int cury;
}

void console_init(struct console_dev *dev);
void console_print(struct console_dev *dev, const char *string);
