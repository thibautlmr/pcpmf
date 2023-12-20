using FinancialApp;
using ParameterInfo;
using PricingClient;

class Program
{
    static async Task Main(string[] args)
    { 
        string serverAddress = "http://localhost:50051";
        string[] argsMano = { "C:\\Users\\lamur\\Documents\\3aif\\pcpmf\\pcpmf-project\\params\\test-param5.json", "C:\\Users\\lamur\\Documents\\3aif\\pcpmf\\pcpmf-project\\params\\MarketDataVanilla.csv", "C:\\Users\\lamur\\Documents\\3aif\\pcpmf\\pcpmf-project\\portfolio5.json" };
        Input input = new(argsMano);
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

        for (int t = 1; t < dates.Count; t++)
        {
            computationUtilities.UpdateGetPriceAndDeltasAsyncParameters(dates[t], t, isMonitoringDate, elapsedTime, past);
            priceAndDeltaInfo = await GrpcClientUtil.GetPriceAndDeltasAsync(serverAddress, isMonitoringDate, elapsedTime, past);
            handler.ComputationUtilities.Pricer = priceAndDeltaInfo;
            handler.MarketDataCurrDate = dataUtilities.GetDataFeedForOneDate(dates[t]);
            if (computationUtilities.RebalancingTime(t))
            {
                handler.GetPortfolioValue();
                handler.UpdateCompo();
                handler.AddOutputData(outputDatas);
                handler.MarketDataPrevDate = dataUtilities.GetDataFeedForOneDate(dates[t]);
            }
        }
        File.WriteAllText(dataUtilities.Input.OutputFilePath, dataUtilities.ExportOutputDatas(outputDatas));
        Console.WriteLine("Press any key to exit...");
        Console.ReadKey();
    }
}