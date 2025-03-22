# KG-805g captured files
These files are traces of the USB data captured on the KG-805g radio while making incremental changes to its config. 
The format of the files is:

```
<time>_<read/write>_<active channel>_<setting>_<previous value>_to_<new value>.<ext>
```

For example, the file `1742255771_read_ch03_t-ctc_off_to_67.0.radiotrace` represents the following:
 - The file was generated 1742255771 seconds after the Unix epoch time: `Monday, March 17, 2025 4:56:11 PM GMT-07:00 DST`
 - The USB packets were captured during a read operation from the radio software.
 - The radio was set to channel 3 when the setting was changed.
 - The setting `t-ctc` was changed from `off` to `67.0` from the radio before the read operation took place.
 - The extention is `radiotrace`, meaning it has been formatted to help with memory mapping.

### How to use these files

The files from `1742254165` to `1742257399` represent one setting being changed on the radio, a read operation taken 
from the software, another settings being changed, a read operation, etc. Using the file above as an example, to see
what changes in memory when we change the `t-ctc` setting from `off` to `67.0` on `ch03`, we need to perform a diff 
with the file with the previous timestamp: `1742255734_read_ch03_r-ctc_210.7_to_off.radiotrace`

The files indicating a `write` operation captures a sample write...with all intermediate capture files.

The files from `1742582502` to `1742582635` also represent one setting changed at a time. However, all intermediate 
capture files have been saved.

#### Displaying differences

Running the `show_diffs` script will display the character diff of all files in order. 
