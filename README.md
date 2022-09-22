# SleepKiller

* one of common evasion techniques that used by malwares is delays its basically delaying execution of malicious behavior in order to evade sandboxes and analysts , it can be very annoying to wait for the malware to do the full execution also analysing it in sandboxes can give you false result because sandboxes are programmed to simply wait and watch for a period of time this is why i made this program .

# DETAILS

*  ``Sleep`` Suspends the current thread until the specified condition is met. Execution resumes when one of the following occurs:

    - An I/O completion callback function is called.
    
    - An asynchronous procedure call (APC) is queued to the thread.
    
    - The time-out interval elapses.
    
* it takes 1 parameter ``DWORD`` that represent ``dwMilliseconds`` or how many Milliseconds to wait and it doesnt return a value .

    ![image](https://user-images.githubusercontent.com/60795188/191631985-4fbbbd5a-e47f-47db-b332-42f690b4cd16.png)

* whenever ``Sleep`` gets called it will jump to ``SleepEx`` from ``kernel32.dll`` to perform the execution its like a wrapper around ``SleepEx``

   ![image](https://user-images.githubusercontent.com/60795188/191631746-8a17860c-92dd-455e-9d91-91cc1c0f5a64.png)

* first we patch ``Sleep`` and ``NOP`` the jump then return instantly so no delay performed .

  - Before

     ![image](https://user-images.githubusercontent.com/60795188/191632529-89fd7e79-fc46-420f-bdd3-3a7f000a8268.png)

  - After

    ![image](https://user-images.githubusercontent.com/60795188/191632939-359379c5-47de-4c61-bcf2-81a3f3b51240.png)

# Lastly

* malware may check to see if time was accelerated by getting the timestamp before and after the sleep then compare it ,if the malware gets false calculation, then the malware knows its get patched this trick i will make a bypass for it in the next updates.
