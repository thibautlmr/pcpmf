# MarketDataReader

Namespace: MarketData

Class that permits to read a list or a csv file of share values and return a list of data feeds.

```csharp
public static class MarketDataReader
```

Inheritance [Object](https://docs.microsoft.com/en-us/dotnet/api/system.object) → [MarketDataReader](./marketdata.marketdatareader.md)

## Methods

### **ReadDataFeeds(String)**

Main method for reading the csv file.

```csharp
public static List<DataFeed> ReadDataFeeds(string filename)
```

#### Parameters

`filename` [String](https://docs.microsoft.com/en-us/dotnet/api/system.string)<br>
The path to the csv file.

#### Returns

[List&lt;DataFeed&gt;](https://docs.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1)<br>
The corresponding list of  objects.

### **ReadDataFeeds(List&lt;ShareValue&gt;)**

Main method for reading a list of [ShareValue](./marketdata.sharevalue.md) objects.

```csharp
public static List<DataFeed> ReadDataFeeds(List<ShareValue> shareValues)
```

#### Parameters

`shareValues` [List&lt;ShareValue&gt;](https://docs.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1)<br>
The list of objects.

#### Returns

[List&lt;DataFeed&gt;](https://docs.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1)<br>
The corresponding list of  objects.
