//lintel add 2010/3/8
#ifdef CONFIG_MGB100
#define USB1_GPIO 2 
#define USB2_GPIO 3
#elif defined(CONFIG_MGB111)
#define USB1_GPIO 2
#define USB2_GPIO 3
#else
#define USB1_GPIO 2 
#define USB2_GPIO 3
#endif
 
//  write_gpio(USB1_GPIO, 1);
// write_gpio(USB2_GPIO, 1);
