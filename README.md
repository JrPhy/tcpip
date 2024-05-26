make\
./server_thread ip:port\
in another terminal ./client_thread ip:port

## 1. 流程
| server |  | client | 
| :---: | :---: | :---: | 
| socekt() |  | socekt()  | 
| bind() |  |  | 
| listen() |  |  |
| accept() |  |  |
| 阻塞至連上  | 建立連線 | connect()  | 
| while() | | |
| recv() | <-- | send() |
|  |  |  |
| send() | --> | recv() | 
| end while |  |  | 
| close() | | close() |
| accept() | DATA 包含 const | bss |
