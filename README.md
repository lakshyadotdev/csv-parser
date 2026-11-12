# CSV Parser Memory Layout

## Visual Architecture

```mermaid
flowchart TD
    subgraph DF["DataFrame (Struct)"]
        R["ROWSIZE (size_t)"]
        C["COLSIZE (size_t)"]
        COLS["columns (Column**)"]
    end

    subgraph PTR_ARR["Heap: Contiguous Pointer Array"]
        P0["columns[0] (Column*)"]
        P1["columns[1] (Column*)"]
        P2["columns[2] (Column*)"]
    end

    subgraph COL["Column (Struct)"]
        NAME["name (char*)"]
        TYPE["type = COL_STRING"]
        subgraph DATA["data (Embedded Data Struct)"]
            VALS["values (CellValue*)"]
        end
    end

    subgraph CELL_ARR["Heap: Contiguous CellValue Array"]
        V0["values[0].s (char*)"]
        V1["values[1].s (char*)"]
        V2["values[2].s (char*)"]
    end

    STR_NAME["Heap: &quot;City&quot;"]
    STR_VAL["Heap: &quot;Delhi&quot;"]

    COLS --> PTR_ARR
    P0 --> COL
    NAME --> STR_NAME
    VALS --> CELL_ARR
    V0 --> STR_VAL
```

## Memory Ownership Summary

| Struct / Field | Allocation Type | Contiguous? |
| :--- | :--- | :--- |
| `DataFrame->columns` | `malloc(COLSIZE * sizeof(Column*))` | Yes (array of pointers) |
| `Column` | `malloc(sizeof(Column))` per column | No (individual heap blocks) |
| `Column->data` | Embedded inside `Column` | Yes (part of `Column` block) |
| `Column->data.values` | `malloc(ROWSIZE * sizeof(CellValue))` | Yes (contiguous cell slots) |
