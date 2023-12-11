# ShareValue

Namespace: MarketData

Class that stores the value of the share at a given date.

```csharp
public class ShareValue
```

Inheritance [Object](https://docs.microsoft.com/en-us/dotnet/api/system.object) → [ShareValue](./marketdata.sharevalue.md)

## Properties

### **Id**

Readonly property containing the id of the share.

```csharp
public string Id { get; }
```

#### Property Value

[String](https://docs.microsoft.com/en-us/dotnet/api/system.string)<br>

### **DateOfPrice**

Readonly property containing the considered date.

```csharp
public DateTime DateOfPrice { get; }
```

#### Property Value

[DateTime](https://docs.microsoft.com/en-us/dotnet/api/system.datetime)<br>

### **Value**

Readonly property containing the value of the share.

```csharp
public double Value { get; }
```

#### Property Value

[Double](https://docs.microsoft.com/en-us/dotnet/api/system.double)<br>

## Constructors

### **ShareValue(String, DateTime, Double)**

Constructor for the class.

```csharp
public ShareValue(string id, DateTime dateOfPrice, double value)
```

#### Parameters

`id` [String](https://docs.microsoft.com/en-us/dotnet/api/system.string)<br>
Id of the share.

`dateOfPrice` [DateTime](https://docs.microsoft.com/en-us/dotnet/api/system.datetime)<br>
Date at which the share has the price.

`value` [Double](https://docs.microsoft.com/en-us/dotnet/api/system.double)<br>
Price of the share.
