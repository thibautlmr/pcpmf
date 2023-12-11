# DayCount

Namespace: TimeHandler

Helper class to count the business days between two given dates.

```csharp
public static class DayCount
```

Inheritance [Object](https://docs.microsoft.com/en-us/dotnet/api/system.object) → [DayCount](./timehandler.daycount.md)

## Methods

### **IsBusinessDay(DateTime)**

Tests whether a given date is a business day or not

```csharp
public static bool IsBusinessDay(DateTime date)
```

#### Parameters

`date` [DateTime](https://docs.microsoft.com/en-us/dotnet/api/system.datetime)<br>

#### Returns

[Boolean](https://docs.microsoft.com/en-us/dotnet/api/system.boolean)<br>

### **CountBusinessDays(DateTime, DateTime)**

Counts the number of business days between two dates, excluding the first one and including the last one.

```csharp
public static int CountBusinessDays(DateTime start, DateTime end)
```

#### Parameters

`start` [DateTime](https://docs.microsoft.com/en-us/dotnet/api/system.datetime)<br>
Start date.

`end` [DateTime](https://docs.microsoft.com/en-us/dotnet/api/system.datetime)<br>
End date.

#### Returns

[Int32](https://docs.microsoft.com/en-us/dotnet/api/system.int32)<br>
The number of business days between start date and end date.

### **NextBusinessDay(DateTime)**

Returns the closest business day that follows a given date

```csharp
public static DateTime NextBusinessDay(DateTime current)
```

#### Parameters

`current` [DateTime](https://docs.microsoft.com/en-us/dotnet/api/system.datetime)<br>

#### Returns

[DateTime](https://docs.microsoft.com/en-us/dotnet/api/system.datetime)<br>
