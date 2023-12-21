using FinancialApp;
using ParameterInfo;
using PricingClient;

class Program
{
    static async Task Main(string[] args)
    { 
        string serverAddress = "http://localhost:50051";
        Input input = new(args);
        DataUtilities dataUtilities = new(input);
        double[] spots = dataUtilities.GetSpots(dataUtilities.MarketData[0].Date);
        List<List<double>> past = new() { spots.ToList() };
        List<DateTime> dates = dataUtilities.GetDateTimes(dataUtilities.MarketData);
        bool isMonitoringDate = false;
        double elapsedTime = 0.0;
        Pricer priceAndDeltaInfo = await GrpcClientUtil.GetPriceAndDeltasAsync(serverAddress, isMonitoringDate, elapsedTime, past);
        ComputationUtilities computationUtilities = new(priceAndDeltaInfo, dataUtilities);
        var marketDataCurrDate = dataUtilities.GetDataFeedForOneDate(dates[0]);
        Handler handler = new(computationUtilities, marketDataCurrDate);
        List<OutputData> outputDatas = new();
        handler.AddOutputData(outputDatas);
        for (int t = 1; t < dates.Count; t++)
        {
            handler.MarketDataCurrDate = dataUtilities.GetDataFeedForOneDate(dates[t]);
            if (computationUtilities.RebalancingTime(t))
            {
                computationUtilities.UpdateGetPriceAndDeltasAsyncParameters(dates[t], t, ref isMonitoringDate, ref elapsedTime, ref past);
                priceAndDeltaInfo = await GrpcClientUtil.GetPriceAndDeltasAsync(serverAddress, isMonitoringDate, elapsedTime, past);
                handler.ComputationUtilities.Pricer = priceAndDeltaInfo;
                handler.MarketDataCurrDate = dataUtilities.GetDataFeedForOneDate(dates[t]);
                handler.CurrDate = dates[t];
                handler.UpdateCompo();
                handler.AddOutputData(outputDatas);
                handler.MarketDataPrevDate = dataUtilities.GetDataFeedForOneDate(dates[t]);
                handler.PrevDate = dates[t];
                Console.WriteLine(t);
            }
        }
        File.WriteAllText(dataUtilities.Input.OutputFilePath, dataUtilities.ExportOutputDatas(outputDatas));
        Console.WriteLine("Press any key to exit...");
        Console.ReadKey();
    }
}