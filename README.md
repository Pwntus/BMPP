# BMPP - Bitmap Parser
Bitmap image parser written in C.

### Usage:

```term
$ make
$ ./bmpp <bitmap file> [-json]
```
### JSON output:

```term
JS Obj:
	signature: 		String
	file_size: 		Integer
	reserved_1: 	String
	reserved_2: 	String
	offset: 		String
	info_size: 		Integer
	width: 			Integer
	height: 		Integer
	color_panels: 	Integer
	bpp: 			Integer
	compression: 	String
	img_size: 		Integer
	y_res: 			Integer
	x_res: 			Integer
	n_cpalette: 	Integer
	n_important: 	Integer
```
