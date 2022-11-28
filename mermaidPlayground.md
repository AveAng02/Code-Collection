

```mermaid
flowchart LR
    S[Start] --> A
    A(Enter your user name) --> B{Existing user?}
    B -->|No| C(Register user)
    C --> D{Valid entries?}
    D -->|No| A
    D -->|Yes| E(Send email with link to login)
    B -->|Yes| E
    E --> End
```
